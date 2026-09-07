
#include <gtest/gtest.h>
#include <string_view>
#include <string>

#ifdef KVS_DEMONSTRATE_DANGLING_BUG

namespace {

struct BadCommand {
    std::string_view key;
};

BadCommand make_bad_command() {
    std::string temp = "some-key-that-is-long-enough";
    return BadCommand{std::string_view(temp)};
}

TEST(DanglingDemo, ShowsUseAfterScopeUnderAsan) {
    BadCommand cmd = make_bad_command();
    EXPECT_FALSE(cmd.key.empty());
}

}

#else

TEST(DanglingDemo, ExplanationOnly) {
    GTEST_SKIP() << "Демонстрация бага собирается отдельно с флагом "
                    "-DKVS_DEMONSTRATE_DANGLING_BUG и -fsanitize=address. "
                    "См. комментарий в начале файла.";
}

#endif
