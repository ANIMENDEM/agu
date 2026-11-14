#include <iostream>

int main() {
    std::cout << "EnvironmentTest OK" << std::endl;

    #if defined(_MSC_VER)
        std::cout << "Compiler: MSVC, version: " << _MSC_VER << std::endl;
    #elif defined(__clang__)
        std::cout << "Compiler: Clang, version: " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << std::endl;
    #elif defined(__GNUC__)
        std::cout << "Compiler: GCC, version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
    #else
        std::cout << "Compiler: Unknown" << std::endl;
    #endif

    std::cout << "__cplusplus standard value: " << __cplusplus << std::endl;

    #ifdef NDEBUG
        std::cout << "Build type: Release" << std::endl;
    #else
        std::cout << "Build type: Debug" << std::endl;
    #endif

    std::cout << "Platform pointer size: " << sizeof(void*) * 8 << " bits" << std::endl;

    return 0;
}