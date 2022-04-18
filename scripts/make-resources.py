srcdir = "resources/"


if __name__ == "__main__":
    import os
    import base64
    from glob import glob

    out = open("build/resources.cpp", "w")

    lines = []
    lines.append("#include \"engine/resources.hpp\"")
    lines.append("#include <unordered_map>")
    lines.append("")
    files = [fn for fn in glob(f"{srcdir}**", recursive=True) if not os.path.isdir(fn)]

    # make resource arrays
    vars = list()

    lines.append("// RESOURCE ARRAYS")

    for i, fn in enumerate(files):
        with open(fn, "rb") as f:
            # correct to relative filename (cut off res dir)
            fn = fn[len(srcdir):]

            # generate var name and content
            varname = f"res_{i}"
            data = [str(b) for b in f.read()]
            arr = "{" + ",".join(data) + "}"

            lines.append(f"static const char {varname}[] = {arr};")
            vars.append((fn, varname, len(data)))
    lines.append("")

    # make hashmap

    lines.append("// RESOURCE MAP")
    lines.append("static const std::unordered_map<std::string, Resource> res_map =")
    lines.append("{")

    for fn, name, size in vars:
        quotfn = "\"" + fn + "\""
        line = "\t{" + quotfn + ", {" + f".path={quotfn}, .data={name}, .size={size}"  +"}},"
        lines.append(line)

    lines.append("};")

    out.write("\n".join(lines))


