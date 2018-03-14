extern char *s_gets(char *st,int n);//外部函数，告知编译器定义（definition）在别处查询
//且编译器会检查该声明是否和定义相一致
//这样如果多个文件使用一个函数，只需要在一个.c 文件中定义，在头文件中声明（最好显示加extern，虽然default是extern）
//如果这个定义需要更改，只需要重新编译实现该函数定义的.c 文件，不需要全部重新编译。
//int i;//会被初始化为0；
//extern int i;//不会被初始化