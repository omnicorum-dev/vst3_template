import os

config_file = open("config.txt", "r")

project_name = ""
plugin_name = ""
project_version = ""
company_name = ""
company_copyright = ""
company_website = ""
company_email = ""

processor_uid = ""
controller_uid = ""

vst3_sdk_path = ""

tag = ""

for line in config_file:
    line = line.strip()
    if not line:
        continue
    for c in line:
        if c != ":":
            tag += c
        else:
            break
    line = line.replace(tag + ": ", "")
    line = line.strip()
    if tag == "ProjectName":
        project_name = line
    elif tag == "ProjectVersion":
        project_version = line
    elif tag == "PluginName":
        plugin_name = line
    elif tag == "CompanyName":
        company_name = line
    elif tag == "CompanyCopyright":
        company_copyright = line
    elif tag == "CompanyWebsite":
        company_website = line
    elif tag == "CompanyEmail":
        company_email = line
    elif tag == "ProcessorUID":
        processor_uid = line
    elif tag == "ControllerUID":
        controller_uid = line
    elif tag == "VST3_SDK_Path":
        vst3_sdk_path = line

    tag = ""

namespace_name = project_name[0].capitalize() + project_name[1:]

company_name_lower = company_name.lower()
project_name_lower = project_name.lower()

puid = (
    processor_uid[0:10]
    + ", 0x"
    + processor_uid[11:19]
    + ", 0x"
    + processor_uid[20:28]
    + ", 0x"
    + processor_uid[29:]
)

cuid = (
    controller_uid[0:10]
    + ", 0x"
    + controller_uid[11:19]
    + ", 0x"
    + controller_uid[20:28]
    + ", 0x"
    + controller_uid[29:]
)

print(f"      project_name: {project_name}")
print(f"    namespace_name: {namespace_name}")
print(f"   project_version: {project_version}")
print(f"       plugin_name: {plugin_name}")
print(f"      company_name: {company_name}")
print(f" company_copyright: {company_copyright}")
print(f"   company_website: {company_website}")
print(f"     company_email: {company_email}")
print(f"     processor_uid: {processor_uid}")
print(f"    controller_uid: {controller_uid}")
print(f"     vst3_sdk_path: {vst3_sdk_path}")
print(f"company_name_lower: {company_name_lower}")
print(f"project_name_lower: {project_name_lower}")
print(f"              puid: {puid}")
print(f"              cuid: {cuid}")

if not os.path.isdir("./src"):
    os.mkdir("./src")

with open("template_files/plugin.h") as f:
    contents = f.read()
contents = contents.replace("|NAMESPACENAME|", namespace_name)
contents = contents.replace("|PROCESSORUID|", puid)
contents = contents.replace("|CONTROLLERUID|", cuid)
with open("src/plugin.h", "w") as f:
    f.write(contents)

with open("template_files/plugin.cpp") as f:
    contents = f.read()
contents = contents.replace("|PLUGINNAME|", plugin_name)
contents = contents.replace("|NAMESPACENAME|", namespace_name)
contents = contents.replace("|COMPANYNAME|", company_name)
contents = contents.replace("|COMPANYWEBSITE|", company_website)
contents = contents.replace("|COMPANYEMAIL|", company_email)
with open("src/plugin.cpp", "w") as f:
    f.write(contents)

with open("template_files/controller.h") as f:
    contents = f.read()
contents = contents.replace("|NAMESPACENAME|", namespace_name)
with open("src/controller.h", "w") as f:
    f.write(contents)

with open("template_files/controller.cpp") as f:
    contents = f.read()
contents = contents.replace("|NAMESPACENAME|", namespace_name)
with open("src/controller.cpp", "w") as f:
    f.write(contents)

with open("template_files/processor.h") as f:
    contents = f.read()
contents = contents.replace("|NAMESPACENAME|", namespace_name)
with open("src/processor.h", "w") as f:
    f.write(contents)

with open("template_files/processor.cpp") as f:
    contents = f.read()
contents = contents.replace("|NAMESPACENAME|", namespace_name)
with open("src/processor.cpp", "w") as f:
    f.write(contents)

with open("template_files/CMakeLists.txt") as f:
    contents = f.read()
contents = contents.replace("|PROJECTNAMELOWER|", project_name_lower)
contents = contents.replace("|PROJECTNAME|", project_name)
contents = contents.replace("|VST3SDKPATH|", vst3_sdk_path)
contents = contents.replace("|COMPANYNAME|", company_name)
contents = contents.replace("|COMPANYNAMELOWER|", company_name_lower)
with open("CMakeLists.txt", "w") as f:
    f.write(contents)


config_file.close()
