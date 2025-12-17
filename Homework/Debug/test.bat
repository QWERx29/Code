
rem --------------------------------
rem	取指定配置文件的所有组/组中所有项
rem --------------------------------
test_readcfg --cfgfile httpd.conf
pause
test_readcfg --cfgfile httpd.conf --group all
pause
test_readcfg --cfgfile php.ini
pause
test_readcfg --cfgfile php.ini --group all
pause
test_readcfg --cfgfile my.cnf
pause
test_readcfg --cfgfile yzmond.conf
pause

rem --------------------------------------
rem 	取指定配置文件的指定组中所有项的原始内容
rem --------------------------------------
test_readcfg --cfgfile httpd.conf --group ""
pause
test_readcfg --cfgfile php.ini --group [MSSQL]
pause
test_readcfg --cfgfile php.ini --group [mssql]
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs
rem 大小写敏感，报组找不到
test_readcfg --cfgfile php.ini --group [mssql] --gcs
pause
test_readcfg --cfgfile my.cnf --group ""
pause
test_readcfg --cfgfile my.cnf --group "[mysqld]"
pause
test_readcfg --cfgfile yzmond.conf --group "[数据库]"
pause

rem ----------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值的原始内容（必须是 "项目名 =/空格/tab 值" 形式的项，否则报找不到）
rem ----------------------------------------------------------------------------------------------------------
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.max_links
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs --item mssql.max_links
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs --item mssql.max_links --ics
pause
rem 报找不到
test_readcfg --cfgfile php.ini --group [mssql] --gcs --item mssql.max_links
pause
rem 报找不到
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.MAX_links --ics
pause
rem 报找不到
test_readcfg --cfgfile php.ini --group [mssql] --gcs --item mssql.max_links --ics
pause

rem httpd.conf 的分隔符是空格，报找不到
test_readcfg --cfgfile httpd.conf --group "" --item EnableSendfile
pause
rem 指定分隔符为空格/tab，找到
test_readcfg --cfgfile httpd.conf --group "" --item EnableSendfile --brkchar space
pause
rem 指定分隔符为空格/tab，找出来错的内容，这不是程序错（程序员必须明确知道配置文件的格式）
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.max_links --brkchar space
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		1、null型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 能取到
test_readcfg --cfgfile yzmond.conf --group [连接设置] --item 允许长连接 --type null
pause
rem 能取到
test_readcfg --cfgfile yzmond.conf --group "[连接设置]" --item "允许长连接" --type null
pause
rem 能取到
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type null
pause
rem 取不到（比上一个测试的item少一个字母）
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_di --type null
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		2、char型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem  三种方式都能取到y
test_readcfg --cfgfile yzmond.conf --group [连接设置] --item 允许长连接 --type char
pause
rem 前两种取不到，第三种取到默认值Y
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type char
pause
rem 第一种取到9（因为任意字符均合法），第二种取不到，因为不在合法集合中且没有默认值，第三种取到默认值Y
test_readcfg --cfgfile yzmond.conf --group [连接设置] --item 设备采样间隔 --type char
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		3、int型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 三种方式都能取到30
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 未应答超时 --type int
pause
rem 第一种取到1000，第二种取不到，第三种取到默认值10
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 队列最大长度 --type int
pause
rem 找到但类型指定错误，按int读，三种均取到60
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 内存使用比例 --type int
pause
rem 前两种取不到，第三种取到默认值10
test_readcfg --cfgfile php.ini --group [Tidy] --item tidy.clean_output --type int
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		4、double型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 三种方式都能取到60.5
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 内存使用比例 --type double
pause
rem 三种方式都能取到30（以double方式读int是兼容的）
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 未应答超时 --type double
pause
rem 第一种取到87.35，第二种取不到，第三种取到默认值1.2
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 内存空载比例 --type double
pause
rem 前两种取不到，第三种取到默认值1.2
test_readcfg --cfgfile php.ini --group [Tidy] --item tidy.clean_output --type double
pause
rem 前两种取不到，第三种取到默认值1.2
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type double
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		5、cstring型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space
pause
rem 返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type raw
pause
rem 三种方式都能取到index.html（第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type cstring
pause

rem 多个LogFormat，只找第一个，返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space
pause
rem 多个LogFormat，只找第一个，三种方式都能取到"%h（未做转义符处理及引号匹配，仅取第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space --type cstring
pause

rem 多个AddType，只找第一个，返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type raw
pause
rem 多个AddType，只找第一个，第一种方式已越界（出什么都不奇怪）；第一种方式注释后，后两种方式都能取到长度为15的串
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type cstring
pause

rem 前两种取不到，第三种取到默认值Hello
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type cstring
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		6、string型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 返回原始内容（含空格的所有），用于和--type string比较
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space
pause
rem 两种方式都能取到index.html（第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type string
pause

rem 多个LogFormat，只找第一个，返回原始内容（含空格的所有），用于和--type string比较
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space
pause
rem 多个LogFormat，只找第一个，三种方式都能取到"%h（未做转义符处理及引号匹配，仅取第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space --type string
pause

rem 多个AddType，只找第一个，返回原始内容（含空格的所有），用于和--type string比较
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type raw
pause
rem 多个AddType，只找第一个，两种方式都能取到完整内容application/x-compress
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type string
pause

rem 第一种取不到，第二种取到默认值Tongji
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type string
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		7、IP地址
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 两种方式都能取到192.9.200.214，打印的是hex（c009c8d6）
test_readcfg --cfgfile yzmond.conf --group [数据采集设置] --item 调试IP地址 --type ip
pause
rem 第一种取不到，第二种取到默认值192.168.1.230（c0a801e6）
test_readcfg --cfgfile yzmond.conf --group [数据库] --item 服务器IP地址 --type ip
pause
rem 第一种取不到，第二种取到默认值192.168.1.230（c0a801e6）
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type ip

rem --------------------------------------------------------------------------------------------------------------------------
rem	测试重复组/重复项
rem		7、IP地址
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem [日志目录]/[数据库]均只有一组，每组两项
test_readcfg --cfgfile homework.conf
pause
rem 指定组名，均取到两项
test_readcfg --cfgfile homework.conf --group [日志目录]
test_readcfg --cfgfile homework.conf --group [数据库]
pause
rem 指定项目名，只返回同名的第一项
test_readcfg --cfgfile homework.conf --group [日志目录] --item logfile
test_readcfg --cfgfile homework.conf --group [数据库] --item db_ip
rem 指定项目名+返回类型，也只返回同名的第一项的对应取值
test_readcfg --cfgfile homework.conf --group [日志目录] --item logfile --type int
test_readcfg --cfgfile homework.conf --group [数据库] --item db_ip --type double