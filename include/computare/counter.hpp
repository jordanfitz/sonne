#pragma once

namespace Computare
{

    struct FileInfo
    {

        std::string language = "Plain Text";
        size_t      files = 0;
        size_t      totalLines = 0;
        size_t      emptyLines = 0;
        size_t      codeLines = 0;
        size_t      commentLines = 0;
        size_t      averageLineLength = 0;

        FileInfo& operator+=(const FileInfo& info)
        {
            this->files += info.files;
            this->totalLines += info.totalLines;
            this->emptyLines += info.emptyLines;
            this->codeLines += info.codeLines;
            this->commentLines += info.commentLines;

            return *this;
        }

    };

    enum class CommentCheckState : uint8_t
    {
        NONE,
        CHECKING
    };

    enum class CountState : uint8_t
    {
        REGULAR,
        LINE_COMMENT,
        BLOCK_COMMENT
    };

    static inline void PrintSingleFileInfo(const FileInfo& info)
    {
        if (!info.language.empty())
            fmt::print("Language: {}\n", info.language);

        fmt::print("Total Line Count: {}\n", info.totalLines);

        if (info.files > 0)
            fmt::print("Total Files: {}\n", info.files);

        if (info.emptyLines > 0)
            fmt::print("Empty Lines: {}\n", info.emptyLines);

        if (info.codeLines > 0)
            fmt::print("Code Lines: {}\n", info.codeLines);

        if (info.commentLines > 0)
            fmt::print("Comment Lines: {}\n", info.commentLines);

        fmt::print("Average Line Length: {}\n", info.averageLineLength);
    }

    class Config;

    /**
     * Class that takes in a file path and counts data about that file such as line
     * count, average line length, and language of the file based on its extension.
     */
    class Counter
    {

    public:

        /**
         * Create a counter for the file at the current path.
         */
        Counter(const std::string& path);

        /**
         * Return a FileInfo struct relating to the metrics of the countable file.
         *
         * Pass in a config for language support.
         */
        FileInfo Count(std::shared_ptr<Config> config);

    private:

        std::string m_path;

        std::string _GetExtension(const std::string& path);

    };
}