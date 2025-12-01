#include <iostream>
#include <vector>
#include "ccformat.h"
#include "ccscan.h"

int main()
{

    std::cerr << "月雨：工具完全免费，如有人收费说明你被骗了。\n";

    // 创建一个类型为 size_t 的 cscan 对象
    chainer::cscan<size_t> t; // 假定为64位，对于32位系统请使用 uint32_t

    std::string packageName; // 添加一个字符串变量来存储包名

    // 获取用户输入的包名
    std::cout << "请输入包名: ";
    std::getline(std::cin, packageName); // 使用 getline 读取一行输入

    // 获取目标进程的 PID
    memtool::base::target_pid = memtool::base::get_pid(packageName.c_str());
    if (memtool::base::target_pid == -1) {
        std::cerr << "找不到进程。\n";
        return -1; // 如果找不到进程则退出
    }

    // 获取目标进程的内存信息
    memtool::extend::get_target_mem();

    // 设置内存范围
    memtool::extend::set_mem_ranges(-2080836);

    // 用户自定义输入
    size_t address; // 存储用户输入的地址
    int layers;     // 存储用户输入的层数
    size_t offset;  // 存储用户输入的偏移量

    // 获取用户输入的地址
    std::cout << "请输入地址（十六进制）: ";
    std::cin >> std::hex >> address; // 读取十六进制输入

    // 获取用户输入的层数
    std::cout << "请输入层数: ";
    std::cin >> layers;

    // 获取用户输入的偏移量
    std::cout << "请输入偏移量（十六进制）: ";
    std::cin >> std::hex >> offset; // 读取十六进制输入

    // 打印获取的指针数量
    std::cout << "指针数量: " << t.get_pointers(0, 0, false, 10, 1 << 20) << std::endl;

    // 使用用户输入的地址
    std::vector<size_t> addr;
    addr.emplace_back(address);

    // 打开文件
    auto f = fopen("1.txt", "wb+");
    if (!f) {
        std::cerr << "无法打开文件进行写入。\n";
        return -1;
    }

    // 扫描指针链
    size_t result = t.scan_pointer_chain(addr, layers, offset, false, 0, f);
    std::cout << "扫描结果: " << result << std::endl; // 使用 std::cout 进行输出

    // 关闭文件
    fclose(f);

    chainer::cformat<size_t> t2;
    auto f2 = fopen("Formatfile[1].txt", "rb+");

    printf("%ld\n", t2.format_bin_chain_data(f2, "2.txt", 0)); // 文件
    //  printf("%ld\n", t2.format_bin_chain_data(f2, "2", 1)); // 文件夹 需要在当前目录有2文件夹

    fclose(f2);
    return 0;
}
