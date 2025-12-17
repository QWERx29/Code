// 2451317 ·ë¾Ãºã ´óÊý¾Ý
#pragma once
#ifndef TXT_COMPARE_H
#define TXT_COMPARE_H

#include <string>
#include <sstream>
using namespace std;

class txt_compare
{
public:
    enum LineEndType
    {
        LET_LF,
        LET_CRLF,
        LET_CR,
        LET_EOF
    };
    static const char* lineend_to_str(LineEndType t);
    struct LineArray
    {
        string* data;
        LineEndType ends[65536];
        int size;
        int capacity;

        LineArray() : data(nullptr), size(0), capacity(0) {}

        LineArray(const LineArray&) = delete;
        LineArray& operator=(const LineArray&) = delete;

        ~LineArray() { delete[] data; }

        void reserve(int cap)
        {
            if (cap <= capacity)
                return;
            string* newdata = new string[cap];
            for (int i = 0; i < size; ++i)
                newdata[i] = data[i];
            delete[] data;
            data = newdata;
            capacity = cap;
        }
        void push_back(const string& s)
        {
            if (size + 1 > capacity)
                reserve(capacity == 0 ? 16 : capacity * 2);
            data[size++] = s;
        }
        void push_back(const string& s, LineEndType e)
        {
            if (size + 1 > capacity)
                reserve(capacity == 0 ? 16 : capacity * 2);

            data[size] = s;
            ends[size] = e;
            size++;
        }
        string& operator[](int i) { return data[i]; }
        const string& operator[](int i) const { return data[i]; }
    };

    txt_compare(const string& file1,
        const string& file2,
        const string& trim_type,
        const string& display_type,
        int lineskip,
        int lineoffset,
        int max_diffnum,
        int max_linenum,
        bool ignore_blank,
        bool not_ignore_linefeed_,
        bool debug);
    void print_ruler_line(int content_col, int content_width);
    void print_hex_block(const std::string& title, const std::string& raw);
    void print_lineend_hex(LineEndType et);
    void print_one_debug_line(int line_idx, const LineArray& arr, int col);
    int apply_offset_and_skip(const LineArray& arr, int offset, int skip, bool ignore_blank);
    void print_eof_difference_block(int disp_l1, int disp_l2, bool eof1, bool eof2, const LineArray& arr1, const LineArray& arr2, int line1, int line2, bool flag);
    void print_normal_line_compare(int disp_l1, int disp_l2, int idx1, int idx2, const string& raw1, const string& raw2, const string& n1, const string& n2, bool cr_diff_mode);
    bool skip_blank_line(const LineArray& arr, int& idx, bool isL1);
    void print_compare_title(int start1, int start2);
    void print_compare_two_lines(const string& raw1, const string& raw2, const string& norm1, const string& norm2, LineEndType end1, LineEndType end2, int first_diff, bool cr_diff_mode);
    void print_debug_summary(int diff_cnt, bool diff_max);
    void print_file_info_block(const string& title, const string& fname, const LineArray& arr, ostringstream& out_stream);
    void update_line_maxlen();
    string make_display_content(const string& raw, const string& norm, LineEndType end);
    void append_lineend(string& s, LineEndType end);
    
    void compare();
    void result();

private:
    string file1_;
    string file2_;
    string trim_type_;    // "none", "left", "right", "all"
    string display_type_; // "normal", "detailed", "none"
    int lineskip_;
    int lineoffset_;
    int max_diffnum_;
    int max_linenum_;
    bool ignore_blank_;
    bool not_ignore_linefeed_;
    //bool CR_CRLF_not_equal_;
    bool debug_;

    LineArray lines1_;
    LineArray lines2_;

    ostringstream out_;
    ostringstream file_info;

    size_t line_maxlen_;

    bool load_file(const string& filename, LineArray& arr, string& err);
    static bool is_space_char(char c);
    int find_CR_pos(const std::string& raw, const std::string& norm) const;
    string trim_copy(const string& s) const;
    string normalize_for_compare(const string& s) const;
    int advance_by_nonblank(const LineArray& arr, int idx, int count) const;
    string make_display_line(const string& norm, LineEndType et) const;
    string make_raw_with_lineend(const string& raw, LineEndType et) const;
};

#endif // TXT_COMPARE_H
