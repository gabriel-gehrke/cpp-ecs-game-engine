#pragma once

#include <cstdio>
#include <string>
#include <optional>

namespace Serialize{

    template<typename SAVE_TYPE>
    bool save_object(const std::string& identifier, const SAVE_TYPE &obj_to_save)
    {
        size_t no_to_write = sizeof (SAVE_TYPE);
        FILE *file = fopen(identifier.c_str(), "w");

        size_t bytes_written = fwrite(&obj_to_save, no_to_write, 1, file);

        fclose(file);
        // if the no of written bytes is not equal to the no of bytes that should have been written
        //  an error occurred
        return bytes_written;
    }


    template<typename SAVE_TYPE>
    std::optional<SAVE_TYPE> read_object(const std::string& identifier)
    {
        size_t no_to_read = sizeof(SAVE_TYPE);
        FILE *file = fopen(identifier.c_str(), "r");

        char ptr[no_to_read];
        size_t bytes_read = fread(ptr, no_to_read, 1, file);
        fclose(file);


        std::optional<SAVE_TYPE> result = std::nullopt;
        if(bytes_read)
            result = std::optional<SAVE_TYPE>(*((SAVE_TYPE*) ptr));

        return result;
    }
}