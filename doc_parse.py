import xml.etree.ElementTree as ET
from os import listdir
from os.path import isfile, join, basename, splitext
files = [f for f in listdir("docs") if isfile(join("docs", f))]


class GDClass:
    def __init__(self, name):
        self.name = name
        self.brief_description = ""
        self.description = ""
        self.members = []
        self.methods = []
        self.signals = []
        self.enums = {}

    def print_class(self):
        s = "# " + self.name + "\n\n"
        s += self.brief_description.strip()
        s += "\n"
        s += "### Description\n\n"
        s += self.description.strip()
        s += "\n"

        if len(self.members) > 0:
            s += "| | |\n"
            s += "----|----\n"
            for m in self.members:
                s += m.print_header()
            s += "\n"

        if len(self.methods) > 0:
            s += "| | |\n"
            s += "----|----\n"
            for m in self.methods:
                s += m.print_header()
            s += "\n"

        if len(self.signals) > 0:
            s += "### Signals\n\n"
            for sig in self.signals:
                s += sig.print()

        if len([m for m in self.members if not(m.description is None)]) > 0:
            s += "### Property Descriptions\n\n"
            for m in self.members:
                s += m.print_desc()

        if len(self.methods) > 0:
            s += "### Method Descriptions\n\n"
            for m in self.methods:
                s += m.print_desc()

        s = s.replace("[code]", "`")
        s = s.replace("[/code]", "`")

        return s



class GDMethod:
    def __init__(self, name):
        self.name = name
        self.description = ""
        self.returns = "void"
        self.attributes = {}
    
    def print_header(self):
        s = self.returns + "|["  + self.name + "](#" + self.name + ")("

        for k in sorted(self.attributes):
            s += self.attributes[k] + ", "

        s = "".join(s.rsplit(", ", 1))
        s += ")\n"

        return s

    def print_desc(self):
        s = "* <a name=\"" + self.name + "\"></a> " + self.returns + " "  + self.name + "("

        for k in sorted(self.attributes):
            s += self.attributes[k] + ", "

        s = "".join(s.rsplit(", ", 1))
        s += ")\n\n"
        s += self.description.strip() + "\n\n"
        s += "----"
        s+= "\n"

        return s

class GDSignal:
    def __init__(self, name):
        self.name = name
        self.description = ""
        self.attributes = {}

    def print(self):
        s = "* " + self.name + "("

        for k in sorted(self.attributes):
            s += self.attributes[k] + ", "

        s = "".join(s.rsplit(", ", 1))
        s += ")\n\n"

        s += self.description.strip() + "\n\n"
        s += "----"
        s += "\n"

        return s

class GDEnum:

    def __init__(self, name):
        self.name = name
        self.members = {}

class GDProperty:
    def __init__(self, name, t, setter, getter, default, description):
        self.name = name
        self.type = t
        self.setter = setter
        self.getter = getter
        self.default = default
        self.description = description

    def print_header(self):
        return  self.type + "|["  + self.name + "](#" + self.name + ")|" + self.default + "\n"

    def print_desc(self):
        if self.description is None:
            return ""

        s = "* <a name=\"" + self.name + "\"></a> " + self.type + " "  + self.name + "\n\n"

        s += "| | |\n"
        s += "|----|----|\n"
        if self.default == "":
            s += "*Default*|`\"\"`\n"
        else: 
            s += "*Default*|`" + self.default + "`\n"
        s += "*Setter*|" + self.setter + "(value)\n"
        s += "*Getter*|" + self.getter + "\n"
    
        s += self.description.strip() + "\n\n"
        s += "----\n"

        return s


def get_method(gdclass, method):
    m = GDMethod(method.attrib["name"])
    for child in method:
        if child.tag == "description":
            m.description = child.text
        elif child.tag == "argument":
            s = child.attrib["name"]  + " : "
            if "enum" in child.attrib:
                s += child.attrib["enum"]
            else:
                s += child.attrib["type"]
            if "default" in child.attrib:
                s += " = " + child.attrib["default"]
            m.attributes[child.attrib["index"]] = s
        elif child.tag == "returns":
            if "enum" in child.attrib:
                m.returns = child.attrib["enum"]
            else:
                m.returns = child.attrib["type"]


    gdclass.methods.append(m)

def get_signal(gdclass, signal):
    m = GDSignal(signal.attrib["name"])
    for child in signal:
        if child.tag == "description":
            m.description = child.text
        elif child.tag == "argument":
            s = child.attrib["name"]  + " : "
            if "enum" in child.attrib:
                s += child.attrib["enum"]
            else:
                s += child.attrib["type"]
            if "default" in child.attrib:
                s += " = " + child.attrib["default"]
            m.attributes[child.attrib["index"]] = s

    gdclass.signals.append(m)

def get_member(gdclass, member):
    m = GDProperty(member.attrib["name"], member.attrib["type"], member.attrib["getter"], member.attrib["setter"], member.attrib["default"], member.text)
    gdclass.members.append(m)

def print_class(file, gdclass):
    f = open(join("docs", splitext(basename(file))[0] + ".md"), "w")
    f.write(gdclass.print_class())
    f.close()

for f in files:
    if splitext(basename(f))[1] != ".xml":
        continue
    print("Parsing " + f)
    tree = ET.parse(join("docs", f))
    root = tree.getroot()
    gdclass = GDClass(root.attrib["name"])
    for child in root:
        if child.tag == "brief_description":
            gdclass.brief_description = child.text
        elif child.tag == "description":
            gdclass.description = child.text
        elif child.tag == "methods":
            for method in child:
                get_method(gdclass, method)
        elif child.tag == "signals":
            for signal in child:
                get_signal(gdclass, signal)
        elif child.tag == "members":
            for member in child:
                get_member(gdclass, member)
    print_class(f, gdclass)