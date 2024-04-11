#include <crt.hpp>
#include <logging.hpp>
#include <memory.hpp>
#include <obfy.hpp>
#include <stl.hpp>

#include <linuxpe/nt/image.hpp>

#include <Windows.h> // GetModuleHandleA

//
// @todo: @es3n1n: add /GL (Whole Program Optimization) and find out how can we avoid
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2268?view=msvc-170
// on MSVC.
//
// Same goes for /LTCG:incremental
//

BOOL __stdcall DllMain(std::uintptr_t, std::uint32_t call_reason, std::uintptr_t) {
    if (call_reason != DLL_PROCESS_ATTACH)
        return TRUE;

    std::string asd = "5";
    LOG_DEBUG("atoi(%s) - %d", asd.c_str(), crt::atoi(asd.c_str()));

    std::uint8_t meme[] = {0x90, 0x90, 0xE8, 0x0, 0x0, 0x0, 0x0, 0x12, 0x13};
    auto occurency = memory::find_ida_sig(make_sig("E8 ?? ?? ?? ??"), meme, meme + _countof(meme));
    LOG_DEBUG("found sig at %p (offset: %lld)", occurency, occurency.cast<uint8_t*>() - meme);

    auto gmh = LI_FN(GetModuleHandleA).cached();
    LOG_DEBUG("gmh: %p (should be %p)", gmh, GetModuleHandleA);

    auto self = memory::address_t(GetModuleHandleA(nullptr));
    auto img = self.cast<win::image_x64_t*>();

    auto sec = img->get_directory(win::directory_id::directory_entry_import);
    if (sec && sec->present()) {
        auto entry_iat = self.offset(sec->rva).cast<win::import_directory_t*>();
        while (entry_iat->characteristics) {
            auto image_name = self.offset(entry_iat->rva_name).cast<char*>();
            LOG_DEBUG("module has imports from: %s", image_name);

            entry_iat++;
        }
    }

    LOG_DEBUG("sqrt(90.f): %f", crt::math::sqrt(90.f));

    LOG_INFO("Hello, %s", "world");
    // INFO :: C:\Users\f4u76\source\repos\sugoi-base\sugoi-base\dllmain.cpp :: L38 >> Hello, world

    LOG_DEBUG("Hello, %s", "debug");

    return TRUE;
}

int main() {
    DllMain(0, DLL_PROCESS_ATTACH, 0);
}
