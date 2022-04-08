if __name__ == "__main__":
    import os
    import base64
    from glob import glob

    out = open("build/resources.cpp", "w")
    out.write("#include \"resources.hpp\"\n\n")
    out.write("const std::unordered_map<std::string, const char[]> resource_map =\n")
    out.write("{\n")

    srcdir = "resources/"

    for fn in glob(f"{srcdir}**", recursive=True):
        if os.path.isdir(fn):
            continue
        with open(fn, "rb") as f:
            content = "{" + ",".join(str(b) for b in f.read()) + "}"
            out.write("\t{")
            out.write(f"\"{fn[len(srcdir):]}\", {content}")
            out.write("},\n")
            print(fn, len(content))

    out.write("};\n")


