// 2451317 冯久恒 大数据
#define _CRT_SECURE_NO_WARNINGS
#include "../include/txt_compare.h"
#include "../include/cmd_console_tools.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <istream>

using namespace std;
static const size_t MAX_LINE_BYTES = 65535;

/*****************************************************************************
  函数名称：show_str/char
  功    能：显示字符(串)
  输入参数：
  返 回 值：
  说    明：
******************************************************************************/
static void show_color_str(int x, int y, const string& s, int bg, int fg)
{
    cct_showstr(x, y, s.c_str(), bg, fg, 1, -1);
}
static void show_diff_char(int x, const char ch) // 背景亮黄(14)，前景红(4)
{
    cct_showch(x, -1, ch, 14, 4, 1);
}
static void show_same_char(int x, const char ch) // 黑底白字
{
    cct_showch(x, -1, ch, 0, 15, 1);
}
static void show_empty_highlight(int col)
{
    cct_showstr(col, -1, "<EMPTY>", 14, 4, 1, -1);
}
/*****************************************************************************
  函数名称：detect_file_format
  功    能：检测文件格式（Windows/Linux）
  输入参数：filename - 文件名
  返 回 值："Windows" / "Linux" / "Unknown"
  说    明：
******************************************************************************/
static string detect_file_format(const string& filename)
{
    ifstream ifs(filename, ios::binary);
    if (!ifs)
        return "Unknown";
    char prev = 0, c;
    while (ifs.get(c))
    {
        if (c == '\n')
        {
            if (prev == '\r')
                return "Windows"; // CRLF
            else
                return "Linux"; // LF
        }
        prev = c;
    }
    return "Unknown";
}
/*****************************************************************************
  函数名称：get_file_size
  功    能：获取文件大小
  输入参数：filename - 文件名
  返 回 值：文件大小（字节），失败返回 -1
  说    明：
*******************************************************************************/
static long get_file_size(const string& filename)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    if (!ifs)
        return -1;
    return (long)ifs.tellg();
}

const char* txt_compare::lineend_to_str(LineEndType t)
{
    switch (t)
    {
    case LET_LF:   return "<LF>";
    case LET_CRLF: return "<CR><LF>";
    case LET_CR:   return "<CR>";
    case LET_EOF:  return "<EOF>";
    default:       return "";
    }
}

static int first_diff_pos(const string& a, const string& b)
{
    int lena = (int)a.size();
    int lenb = (int)b.size();
    int i, m = (lena < lenb ? lena : lenb);

    for (i = 0; i < m; ++i)
        if (a[i] != b[i])
            return i;
    if (lena != lenb)
        return m;
    return -1;
}

//=====================================================================
//      构造函数
//=====================================================================
txt_compare::txt_compare(const string& file1,
    const string& file2,
    const string& trim_type,
    const string& display_type,
    int lineskip,
    int lineoffset,
    int max_diffnum,
    int max_linenum,
    bool ignore_blank,
    bool  not_ignore_linefeed_,
    bool debug)
    : file1_(file1), file2_(file2),
    trim_type_(trim_type),
    display_type_(display_type.empty() ? "none" : display_type),
    lineskip_(lineskip),
    lineoffset_(lineoffset),
    max_diffnum_(max_diffnum),
    max_linenum_(max_linenum),
    ignore_blank_(ignore_blank),
    not_ignore_linefeed_(not_ignore_linefeed_),
    debug_(debug),
    line_maxlen_(0)
{
    silent_ = false;
    use_stream_ = false;
    in1_ = nullptr;
	in2_ = nullptr;
}

txt_compare::txt_compare(std::istream& a, std::istream& b,
    const string& trim_type,
    const string& display_type,
    int lineskip,
    int lineoffset,
    int max_diffnum,
    int max_linenum,
    bool ignore_blank,
    bool not_ignore_linefeed,
    bool debug)
    : file1_("(input_stream)"), file2_("(input_stream)"),
    trim_type_(trim_type),
    display_type_(display_type.empty() ? "none" : display_type),
    lineskip_(lineskip),
    lineoffset_(lineoffset),
    max_diffnum_(max_diffnum),
    max_linenum_(max_linenum),
    ignore_blank_(ignore_blank),
    not_ignore_linefeed_(not_ignore_linefeed),
    debug_(debug),
    line_maxlen_(0)
{
    silent_ = true;
    use_stream_ = true;
    in1_ = &a;
    in2_ = &b;
}
/*****************************************************************************
  函数名称：*
  功    能：打印detailed模式下的标尺行 + HEX块
  输入参数：
  返 回 值：
  说    明：
*******************************************************************************/
void txt_compare::print_ruler_line(int content_col, int content_width)
{
    if (content_width <= 0)
        return;
    string indent(content_col, ' ');
    string line(content_width, '-');
    cct_showstr(1, -1, (indent + line).c_str(), 0, 15, 1, -1);
    putchar('\n');

    string tens(content_width, ' ');
    for (int i = 0; i < content_width; ++i)
    {
        if (i % 10 == 0)
            tens[i] = char('0' + (i / 10) % 10);
    }
    cct_showstr(1, -1, (indent + tens).c_str(), 0, 15, 1, -1);
    putchar('\n');

    string ones(content_width, ' ');
    for (int i = 0; i < content_width; ++i)
        ones[i] = char('0' + (i % 10));
    cct_showstr(1, -1, (indent + ones).c_str(), 0, 15, 1, -1);
    putchar('\n');

    cct_showstr(1, -1, (indent + line).c_str(), 0, 15, 1, -1);
    putchar('\n');
}

void txt_compare::print_hex_block(const string& title, const string& raw)
{
    cct_showstr(1, -1, title.c_str(), 0, 15, 1, -1);
    putchar('\n');

    const unsigned char* data = (const unsigned char*)raw.data();
    size_t len = raw.size();

    size_t offset = 0;
    char linebuf[256];

    while (offset < len)
    {
        size_t chunk = (len - offset > 16 ? 16 : len - offset);

        sprintf(linebuf, "%08x : ", (unsigned int)offset);
        cct_showstr(1, -1, linebuf, 0, 15, 1, -1);

        string hexpart;
        for (size_t i = 0; i < 8; ++i)
        {
            if (i < chunk)
                sprintf(linebuf, "%02x ", data[offset + i]);
            else
                sprintf(linebuf, "   ");
            hexpart += linebuf;
        }

        if (chunk > 8)
            hexpart += "- ";

        for (size_t i = 8; i < 16; ++i)
        {
            if (i < chunk)
                sprintf(linebuf, "%02x ", data[offset + i]);
            else
                sprintf(linebuf, "   ");
            hexpart += linebuf;
        }

        string asc;
        for (size_t i = 0; i < chunk; ++i)
        {
            unsigned char ch = data[offset + i];
            if (ch >= 33 && ch <= 126)
                asc.push_back((char)ch);
            else
                asc.push_back('.');
        }

        cct_showstr(14, -1, hexpart.c_str(), 0, 15, 1, -1);
		putchar(' ');
        if (chunk <= 8)
        {
			putchar(' ');
			putchar(' ');
        }
        cct_showstr(14 + (int)hexpart.size() + 4, -1, asc.c_str(), 0, 15, 1, -1);
        putchar('\n');
        offset += chunk;
    }
}

void txt_compare::print_lineend_hex(LineEndType et)
{
    unsigned char buf[2];
    int n = 0;

    if (et == LET_LF)
        buf[n++] = 0x0a;
    else if (et == LET_CR)
        buf[n++] = 0x0d;
    else if (et == LET_CRLF)
    {
        buf[n++] = 0x0d;
        buf[n++] = 0x0a;
    }
    else if (et == LET_EOF) buf[n++] = 0x1a;

    for (int i = 0; i < n; ++i)
        printf("%02x ", buf[i]);
}

void txt_compare::print_one_debug_line(int line_idx, const LineArray& arr, int col)
{
    const string& raw = arr.data[line_idx];
    string norm = normalize_for_compare(raw);

    string disp = make_display_line(norm, arr.ends[line_idx]);
    cct_showstr(col, -1, disp.c_str(), 0, 15, 1, -1);
}

int txt_compare::apply_offset_and_skip(const LineArray& arr, int offset, int skip, bool ignore_blank)
{
    int idx = 0;

    if (offset < 0)
    {
        int n = -offset;
        if (ignore_blank)
            idx = advance_by_nonblank(arr, idx, n);
        else
            idx = min(arr.size, idx + n);
    }
    else if (offset > 0)
    {
        int n = offset;
        if (ignore_blank)
            idx = advance_by_nonblank(arr, idx, n);
        else
            idx = min(arr.size, idx + n);
    }

    if (skip > 0)
    {
        if (ignore_blank)
            idx = advance_by_nonblank(arr, idx, skip);
        else
            idx = min(arr.size, idx + skip);
    }
    return idx;
}

void txt_compare::print_eof_difference_block(int disp_l1, int disp_l2, bool eof1, bool eof2, const LineArray& arr1, const LineArray& arr2, int line1, int line2, bool flag)
{
    char head[128];
    if (flag)
        sprintf(head, "第[%d / %d]行 - 行结束符不同", disp_l1, disp_l2);
    else
    {
        if (eof1 && !eof2)
            sprintf(head, "第[%d / %d]行 - 文件1已结束/文件2仍有内容", disp_l1, disp_l2);
        else if (!eof1 && eof2)
            sprintf(head, "第[%d / %d]行 - 文件1仍有内容/文件2已结束", disp_l1, disp_l2);
        else if (eof1 && eof2)
            sprintf(head, "第[%d / %d]行 - 行结束符不同", disp_l1, disp_l2);
        else
        {
            if (not_ignore_linefeed_ || flag)
                sprintf(head, "第[%d / %d]行 - 行结束符不同", disp_l1, disp_l2);
            else
                sprintf(head, "");
        }
    }
    cct_showstr(1, -1, head, 0, 15, 1, -1);
    putchar('\n');

    const char* p1 = "文件1 : ";
    const char* p2 = "文件2 : ";
    int col = (strlen(p1) > strlen(p2) ? strlen(p1) : strlen(p2)) + 2;
    // 输出文件1
    if (display_type_ != "none")
    {
        int content_col = max(strlen("文件1 : "), strlen("文件2 : "));
        int len1 = 0;
        int len2 = 0;
        if (!eof1 && line1 < arr1.size)
            len1 = (int)normalize_for_compare(arr1.data[line1]).size();
        if (!eof2 && line2 < arr2.size)
            len2 = (int)normalize_for_compare(arr2.data[line2]).size();
        int maxlen = (len1 > len2 ? len1 : len2);
        int content_width = (maxlen / 10 + 2) * 10 + 1;
        print_ruler_line(content_col, content_width);
    }
    cct_showstr(1, -1, p1, 0, 15, 1, -1);
    if (eof1)
        cct_showstr(col, -1, "<EOF>", 0, 15, 1, -1);
    else
        print_one_debug_line(line1, arr1, col);
    putchar('\n');
    // 输出文件2
    cct_showstr(1, -1, p2, 0, 15, 1, -1);
    if (eof2)
        cct_showstr(col, -1, "<EOF>", 0, 15, 1, -1);
    else
        print_one_debug_line(line2, arr2, col);
    putchar('\n');
    if (display_type_ == "detailed")
    {
        if (!eof1)
        {
            string trimmed1 = normalize_for_compare(arr1.data[line1]);
            string hex1 = make_raw_with_lineend(trimmed1, arr1.ends[line1]);
            print_hex_block("文件1(HEX) : ", hex1);
        }
        else
        {
            unsigned char eof = 0x1a;
            string s;
            s.push_back((char)eof);
            print_hex_block("文件1(HEX) : ", s);
        }
        if (!eof2)
        {
            string trimmed2 = normalize_for_compare(arr2.data[line2]);
            string hex2 = make_raw_with_lineend(trimmed2, arr2.ends[line2]);
            print_hex_block("文件2(HEX) : ", hex2);
        }
        else
        {
            unsigned char eof = 0x1a;
            string s;
            s.push_back((char)eof);
            print_hex_block("文件2(HEX) : ", s);
        }
    }
    putchar('\n');
}

void txt_compare::print_normal_line_compare(int disp_l1, int disp_l2, int idx1, int idx2, const string& raw1, const string& raw2, const string& n1, const string& n2, bool cr_diff_mode)
{
    int len1 = (int)n1.size();
    int len2 = (int)n2.size();
    int maxlen = (len1 > len2 ? len1 : len2);

    int first_diff = -1;
    for (int i = 0; i < maxlen; i++)
    {
        char c1 = (i < len1 ? n1[i] : ' ');
        char c2 = (i < len2 ? n2[i] : ' ');
        if (c1 != c2)
        {
            first_diff = i;
            break;
        }
    }
	bool trim_enabled = trim_type_ != "none";
    bool lf_equal = true;
    if (!trim_enabled && cr_diff_mode)
        lf_equal = (lines1_.ends[idx1] == lines2_.ends[idx2]);
    const bool text_equal = (first_diff < 0);
    const bool equal = text_equal && lf_equal;
    
    char head[128];
    if (!equal && first_diff >= 0)
        sprintf(head, "第[%d / %d]行 - 第[%d]个字符开始有差异", disp_l1, disp_l2, first_diff);
    else
        sprintf(head, "第[%d / %d]行 - 行结束符不同", disp_l1, disp_l2);

    cct_showstr(1, -1, head, 0, 15, 1, -1);
    putchar('\n');
    
    if (display_type_ != "none")
    {
        const int content_col = max(strlen("文件1 : "), strlen("文件2 : "));
        int ruler_len = (maxlen / 10 + 2) * 10 + 1;
        print_ruler_line(content_col, ruler_len);
    }
    print_compare_two_lines(raw1, raw2, n1, n2, lines1_.ends[idx1], lines2_.ends[idx2], first_diff, cr_diff_mode && !trim_enabled);
    if (display_type_ == "detailed")
    {
        string hex1 = n1;
        string hex2 = n2;
        append_lineend(hex1, lines1_.ends[idx1]);
        append_lineend(hex2, lines2_.ends[idx2]);
        print_hex_block("文件1(HEX) : ", hex1);
        print_hex_block("文件2(HEX) : ", hex2);
    }
    putchar('\n');
}

bool txt_compare::skip_blank_line(const LineArray& arr, int& idx, bool isL1)
{
    if (idx >= arr.size)
        return false;
    string norm = normalize_for_compare(arr.data[idx]);
    if (!norm.empty())
        return false;
    if (debug_)
    {
        char buf[64];
        if (isL1)
            sprintf(buf, "第[%d / *] - 为空：忽略.", idx + 1);
        else
            sprintf(buf, "第[* / %d] - 为空：忽略.", idx + 1);
        cct_showstr(1, -1, buf, 0, 15, 1, -1);
        putchar('\n');
        putchar('\n');
    }
    idx++;
    return true;
}

void txt_compare::print_compare_title(int start1, int start2)
{
    cct_showstr(1, -1, "比较结果输出：", 0, 15, 1, -1);
    putchar('\n');
    int width = (line_maxlen_ / 10 + 1) * 10 + 8 + 2;
    if (display_type_ == "detailed" && width < 80)
        width = 80;
    cct_showch(1, -1, '=', 0, 15, width);
    putchar('\n');
    char buf2[64];
    if (debug_)
    {
        sprintf(buf2, "起始行：%d / %d", start1, start2);
        cct_showstr(1, -1, buf2, 0, 15, 1, -1);
        putchar('\n');
    }
}

void txt_compare::print_compare_two_lines(const string& raw1, const string& raw2, const string& norm1, const string& norm2, LineEndType end1, LineEndType end2, int first_diff, bool cr_diff_mode)
{
    const char* prefix1 = "文件1 : ";
    const char* prefix2 = "文件2 : ";
    int prefix_len1 = (int)strlen(prefix1);
    int prefix_len2 = (int)strlen(prefix2);

    int content_col = (prefix_len1 > prefix_len2 ? prefix_len1 : prefix_len2) + 2;

    int len1 = (int)norm1.size();
    int len2 = (int)norm2.size();
    int maxlen = (len1 > len2 ? len1 : len2);

    bool end11 = false;
    bool end22 = false;
    
    // ------------- 文件1 -------------
    cct_showstr(1, -1, prefix1, 0, 15, 1, -1);
    for (int i = 0; i < maxlen; ++i)
    {
        if (i >= len1)
            break;
        char c1 = norm1[i];
        char c2 = (i < len2 ? norm2[i] : ' ');
        if (i < first_diff || first_diff < 0)
            show_same_char(content_col + i, c1);
        else
        {
            if (c1 != c2)
                show_diff_char(content_col + i, c1);
            else
                show_same_char(content_col + i, c1);
        }
    }
    string disp1 = make_display_line(norm1, end1);
    int visible_len = (int)norm1.size();
    int tail_len = (int)disp1.size() - visible_len;
    if (tail_len > 0)
    {
        const char* tail = disp1.c_str() + visible_len;
        cct_showstr(content_col + visible_len, -1, tail, 0, 15, 1, -1);
    }
    putchar('\n');

    // ------------- 文件2 -------------
    cct_showstr(1, -1, prefix2, 0, 15, 1, -1);

    for (int i = 0; i < maxlen; ++i)
    {
        if (i >= len2)
            break;

        char c2 = norm2[i];
        char c1 = (i < len1 ? norm1[i] : ' ');

        if (i < first_diff || first_diff < 0)
            show_same_char(content_col + i, c2);
        else
        {
            if (c1 != c2)
                show_diff_char(content_col + i, c2);
            else
                show_same_char(content_col + i, c2);
        }
    }

    string disp2 = make_display_line(norm2, end2);
    int visible_len2 = (int)norm2.size();
    int tail_len2 = (int)disp2.size() - visible_len2;
    if (tail_len2 > 0)
    {
        const char* tail = disp2.c_str() + visible_len2;
        cct_showstr(content_col + visible_len2, -1, tail, 0, 15, 1, -1);
    }

    putchar('\n');
    
}

void txt_compare::print_debug_summary(int diff_cnt, bool diff_max)
{
    int width = (line_maxlen_ / 10 + 1) * 10 + 8 + 2;
    if (display_type_ == "detailed" && width < 80)
        width = 80;
    if (diff_cnt > 0)
    {
        for (int i = 0; i < width; ++i)
            out_ << "=";
        out_ << '\n';
        out_ << "在指定检查条件下共" << diff_cnt << "行有差异";
        if (diff_max)
            out_ << "[已到设定的最大差异值]";
        out_ << ".\n";
        out_ << "阅读提示：\n";
        out_ << "\t1、每行的行结束符用<CR>/<LF>/<CR><LF>/<EOF>标出(方便看清行结束符的类型)\n";
        out_ << "\t2、如果每行仅有<CR>/<LF>/<CR><LF>/<EOF>，则表示空行\n";
        out_ << "\t3、文件结束标记为<EOF>\n";
        out_ << "\t4、两行相同列位置的差异字符用亮色标出\n";
        out_ << "\t5、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)\n";
        out_ << "\t6、每行尾的多余的字符用亮色标出，VT/BS/BEL用亮色X标出(方便看清隐含字符)\n";
        out_ << "\t7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出\n";
        if (display_type_ != "detailed")
            out_ << "\t8、用--display detailed可以得到更详细的信息\n";
    }
    else
        out_ << "在指定检查条件下完全一致.\n";
    for (int i = 0; i < width; ++i)
        out_ << "=";
    out_ << '\n';
}

void txt_compare::print_file_info_block(const string& title, const string& fname, const LineArray& arr, ostringstream& out_stream)
{
    size_t maxlen = 0;
    int i;
    for (i = 0; i < arr.size; ++i)
    {
        if (arr.data[i].size() > maxlen)
            maxlen = arr.data[i].size();
    }

    long fsize = get_file_size(fname);
    string fmt = detect_file_format(fname);
    int width = (line_maxlen_ / 10 + 1) * 10 + 8 + 2;
    if (display_type_ == "detailed" && width < 80)
        width = 80;
    out_stream << title << "\n";
    for (int i = 0; i < width; ++i)
        out_stream << "=";
    out_stream << '\n';
    out_stream << "文 件 名：" << fname << "\n";
    out_stream << "大    小：" << fsize << "\n";
    out_stream << "行    数：" << arr.size << "\n";
    out_stream << "最大行长：" << maxlen << "\n";
    out_stream << "文件格式：" << fmt << "\n";
    for (int i = 0; i < width; ++i)
        out_stream << "=";
    out_stream << '\n';
}

void txt_compare::update_line_maxlen()
{
    line_maxlen_ = 0;

    for (int i = 0; i < lines1_.size; ++i)
    {
        size_t len = (int)normalize_for_compare(lines1_.data[i]).size();
        if (len > line_maxlen_)
            line_maxlen_ = len;
    }

    for (int i = 0; i < lines2_.size; ++i)
    {
        size_t len = (int)normalize_for_compare(lines2_.data[i]).size();
        if (len > line_maxlen_)
            line_maxlen_ = len;
    }
}

string txt_compare::make_display_content(const string& raw, const string& norm, LineEndType end)
{
    string s = norm;
    if (not_ignore_linefeed_)
    {
        if (end == LET_CR)
            s.push_back('\r');
        else if (end == LET_LF)
            s.push_back('\n');
        else if (end == LET_CRLF)
        {
            s.push_back('\r');
            s.push_back('\n');
        }
    }
    return s;
}

void txt_compare::append_lineend(string& s, LineEndType end)
{
    switch (end)
    {
    case LET_CR:
        s.push_back('\r');
        break;
    case LET_LF:
        s.push_back('\n');
        break;
    case LET_CRLF:
        s.push_back('\r');
        s.push_back('\n');
        break;
    default:
        break;
    }
}

bool txt_compare::is_space_char(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool txt_compare::load_file(const string& f, LineArray& arr, string& err)
{
    arr.size = 0;
    ifstream ifs(f, ios::binary);
    if (!ifs)
    {
        err = "文件[" + f + "]无法打开.";
        return false;
    }
    char c;
    string line;
    while (true)
    {
        line.clear();
        LineEndType et = LET_EOF;
        bool has_char = false;

        while (ifs.get(c))
        {
            has_char = true;

            if (c == '\r')
            {
                if (ifs.peek() == '\n')
                {
                    ifs.get();
                    et = LET_CRLF;
                }
                else
                    et = LET_CR;
                break;
            }
            else if (c == '\n')
            {
                et = LET_LF;
                break;
            }
            else
                line.push_back(c);
        }
        if (!has_char)
            break;
        if (!ifs)
            et = LET_EOF;
        arr.push_back(line, et);
        if (!ifs)
            break;
    }

    return true;
}

bool txt_compare::load_from_stream(std::istream* input, LineArray& arr, string& err)
{
    arr.size = 0;

    if (!input) 
    {
        err = "流为空.";
        return false;
    }

    input->clear();
    input->seekg(0, std::ios::beg);

    char c;
    string line;
    while (true)
    {
        line.clear();
        LineEndType et = LET_EOF;
        bool has_char = false;

        while (input->get(c))
        {
            has_char = true;

            if (c == '\r')
            {
                if (input->peek() == '\n')
                {
                    input->get();
                    et = LET_CRLF;
                }
                else
                    et = LET_CR;
                break;
            }
            else if (c == '\n')
            {
                et = LET_LF;
                break;
            }
            else
                line.push_back(c);
        }
        if (!has_char)
            break;
        if (!*input)
            et = LET_EOF;
        arr.push_back(line, et);
        if (!*input)
            break;
    }
    return true;
}

int txt_compare::find_CR_pos(const string& raw, const string& norm) const
{
    return (int)norm.size();
}

string txt_compare::trim_copy(const string& s) const
{
    if (trim_type_ == "none")
        return s;

    int i = 0, j = (int)s.size();
    if (trim_type_ == "left" || trim_type_ == "all")
        while (i < j && is_space_char(s[i]))
            i++;
    if (trim_type_ == "right" || trim_type_ == "all")
        while (j > i && is_space_char(s[j - 1]))
            j--;
    return s.substr(i, j - i);
}

string txt_compare::normalize_for_compare(const string& s) const
{
    return trim_copy(s);
}

int txt_compare::advance_by_nonblank(const LineArray& arr, int idx, int count) const
{
    while (idx < arr.size && count > 0)
    {
        string t = trim_copy(arr[idx]);
        if (!t.empty())
            count--;
        idx++;
    }
    return idx;
}

string txt_compare::make_display_line(const string& norm,    LineEndType et) const
{
    string s = norm;
    s += lineend_to_str(et);
    return s;
}

string txt_compare::make_raw_with_lineend(const string& raw, LineEndType et) const
{
    string s = raw;
    switch (et)
    {
    case LET_LF:
        s.push_back('\n');        // 0a
        break;
    case LET_CR:
        s.push_back('\r');        // 0d
        break;
    case LET_CRLF:
        s.push_back('\r');        // 0d
        s.push_back('\n');        // 0a
        break;
    case LET_EOF:
        s.push_back(0x1a);        // 1a
        break;
    default:
        break;
    }
    return s;
}

int txt_compare::compare()
{
    std::istream* f1 = nullptr;
    std::istream* f2 = nullptr;
    std::ifstream file1, file2;

    if (use_stream_) 
    {
        string err;
        if (!load_from_stream(in1_, lines1_, err))
        {
            out_ << "第1个" << err << "\n";
            return -1;
        }
        if (!load_from_stream(in2_, lines2_, err))
        {
            out_ << "第2个" << err << "\n";
            return -1;
        }

        f1 = in1_;
        f2 = in2_;
    }

    else 
    {
        file1.open(file1_.c_str());
        file2.open(file2_.c_str());

        string err;
        if (!load_file(file1_, lines1_, err))
        {
            out_ << "第1个" << err << "\n";
            return -1;
        }
        if (!load_file(file2_, lines2_, err))
        {
            out_ << "第2个" << err << "\n";
            return -1;
        }
        f1 = &file1;
        f2 = &file2;
    }

    out_.str("");
    out_.clear();
    file_info.str("");
    file_info.clear();


    update_line_maxlen();

    if (debug_)
    {
        print_file_info_block("第1个文件的基本信息：", file1_, lines1_, file_info);
        print_file_info_block("第2个文件的基本信息：", file2_, lines2_, file_info);
		if (!silent_)
            std::cout << file_info.str();
    }
    
    int line1 = 0;
    int line2 = 0;

    if (lineoffset_ > 0)
    {
        line1 = apply_offset_and_skip(lines1_, 0, 0, ignore_blank_);
        line2 = apply_offset_and_skip(lines2_, lineoffset_, 0, ignore_blank_);
    }
    else if (lineoffset_ < 0)
    {
        line1 = apply_offset_and_skip(lines1_, -lineoffset_, 0, ignore_blank_);
        line2 = apply_offset_and_skip(lines2_, 0, 0, ignore_blank_);
    }
    else
    {
        line1 = 0;
        line2 = 0;
    }

    if (lineskip_ > 0)
    {
        if (ignore_blank_)
        {
            line1 = advance_by_nonblank(lines1_, line1, lineskip_);
            line2 = advance_by_nonblank(lines2_, line2, lineskip_);
        }
        else
        {
            line1 = min(lines1_.size, line1 + lineskip_);
            line2 = min(lines2_.size, line2 + lineskip_);
        }
    }

    int diff_cnt = 0;
    int compared = 0;
    bool diff_max = false;
    bool title_printed = false;

    const bool user_display = (display_type_ != "none" && !silent_);
    const bool show_line_detail = user_display || debug_;

    if (user_display)
    {
        print_compare_title(line1, line2);
        title_printed = true;
    }

    while (true)
    {
        bool eof1 = (line1 >= lines1_.size);
        bool eof2 = (line2 >= lines2_.size);

        if (eof1 && eof2)
            break;

        int disp_l1 = eof1 ? lines1_.size + 1 : line1 + 1;
        int disp_l2 = eof2 ? lines2_.size + 1 : line2 + 1;

        if (ignore_blank_)
        {
            bool skipped1 = false, skipped2 = false;

            if (!eof1)
                skipped1 = skip_blank_line(lines1_, line1, true);
            if (!eof2)
                skipped2 = skip_blank_line(lines2_, line2, false);

            if (skipped1 || skipped2)
                continue;
        }

        compared++;
        if (max_linenum_ > 0 && compared > max_linenum_)
            break;
        const string& raw1 = lines1_[line1];
        const string& raw2 = lines2_[line2];

        string norm1 = normalize_for_compare(raw1);
        string norm2 = normalize_for_compare(raw2);

        bool empty1 = norm1.empty();
        bool empty2 = norm2.empty();
        bool lf_equal = true;
        bool extra1 = !eof1 && raw1.size() > norm1.size();
        bool extra2 = !eof2 && raw2.size() > norm2.size();

        // 行结束符不同判断
        bool end_diff_only = !eof1 && !eof2 && lines1_.ends[line1] != lines2_.ends[line2];
        if (not_ignore_linefeed_)
            lf_equal = (lines1_.ends[line1] == lines2_.ends[line2]);

        if (eof1 || eof2)
        {
            diff_cnt++;
            if(user_display)
            {
                if (empty1 && empty2)
                    print_eof_difference_block(disp_l1, disp_l2, eof1, eof2, lines1_, lines2_, line1, line2, true);
                else
                    print_eof_difference_block(disp_l1, disp_l2, eof1, eof2, lines1_, lines2_, line1, line2, false);
                    
                //print_eof_difference_block(disp_l1, disp_l2, eof1, eof2, lines1_, lines2_, line1, line2, false);
            }
            if (max_diffnum_ > 0 && diff_cnt >= max_diffnum_)
                diff_max = true;
            break;
        }
        else if (empty1 || empty2)
        {
            if (!empty1 && empty2)
            {
                diff_cnt++;

                if (user_display)
                {
                    char head[128];
                    sprintf(head, "第[%d / %d]行 - 文件1有多余字符", disp_l1, disp_l2);
                    cct_showstr(1, -1, head, 0, 15, 1, -1);
                    //putchar('\n');
                    print_eof_difference_block(disp_l1, disp_l2, false, false, lines1_, lines2_, line1, line2, false);
                }
                if (max_diffnum_ > 0 && diff_cnt >= max_diffnum_)
                {
                    diff_max = true;
                    break;
                }
                line1++;
                line2++;
                continue;
            }
            if (empty1 && !empty2)
            {
                diff_cnt++;
                if (user_display)
                {
                    char head[128];
                    sprintf(head, "第[%d / %d]行 - 文件2有多余字符", disp_l1, disp_l2);
                    cct_showstr(1, -1, head, 0, 15, 1, -1);
                    //putchar('\n');
                    print_eof_difference_block(disp_l1, disp_l2, false, false, lines1_, lines2_, line1, line2, false);
                }
                if (max_diffnum_ > 0 && diff_cnt >= max_diffnum_)
                {
                    diff_max = true;
                    break;
                }
                line1++;
                line2++;
                continue;
            }
        }
        else if (norm1 == norm2 && !lf_equal)
        //else if (norm1 == norm2)
        {
            // 检查是否仅是尾部空格差异
            bool extra_space1 = (trim_copy(raw1) != raw1);
            bool extra_space2 = (trim_copy(raw2) != raw2);

            if (extra_space1 && !extra_space2)
            {
                diff_cnt++;
                if (user_display)
                {
                    char head[128];
                    sprintf(head, "第[%d / %d]行 - 文件1尾部有多余字符", disp_l1, disp_l2);
                    cct_showstr(1, -1, head, 0, 15, 1, -1);
                    print_eof_difference_block(disp_l1, disp_l2, false, false, lines1_, lines2_, line1, line2, false);
                }
            }
            else if (!extra_space1 && extra_space2)
            {
                diff_cnt++;
                if (user_display)
                {
                    char head[128];
                    sprintf(head, "第[%d / %d]行 - 文件2尾部有多余字符", disp_l1, disp_l2);
                    cct_showstr(1, -1, head, 0, 15, 1, -1);
                    print_eof_difference_block(disp_l1, disp_l2, false, false, lines1_, lines2_, line1, line2, false);
                }
            }
            else
            {
                // 真正的行结束符不同
                diff_cnt++;
                if (user_display)
                    print_eof_difference_block(disp_l1, disp_l2, false, false, lines1_, lines2_, line1, line2, false);
            }
        }
        else if (norm1 != norm2)
        {
            diff_cnt++;
            if (show_line_detail)
                print_normal_line_compare(disp_l1, disp_l2, line1, line2, raw1, raw2, norm1, norm2, not_ignore_linefeed_);
        }
        if (max_diffnum_ > 0 && diff_cnt >= max_diffnum_)
        {
            diff_max = true;
            break;
        }
        line1++;
        line2++;

    }

    if (user_display)
        print_debug_summary(diff_cnt, diff_max);
    else
        out_ << (diff_cnt > 0 ? "文件不同.\n" : "文件相同.\n");

	return diff_cnt;
}

void txt_compare::result()
{
	if (!silent_)
        std::cout << out_.str();
}
