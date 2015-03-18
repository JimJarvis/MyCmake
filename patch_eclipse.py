# Eclipse will not index and highlight the source files correctly 
# if the sources are split into separate directories. 
# We can make the following modification:
#
# .project
# <linkedResources> 
# <link> </link> will show in Project Explorer. Correct the bad cmake '[Source directory]
#
# .cproject
# MAKE SURE YOU MARK the updated links in .project as "src"
# <pathentry kind="src" path="[Source directory]"/>

from sys import argv, stderr
import os

if not 2 <= len(argv) <= 3:
    print >> stderr, "Usage: python {} <eclipse_project_dir (cmake build dir)> [1 = add gtest folder]".format(argv[0])
    exit()

addGtest = len(argv) == 3 and argv[-1] == '1'
projpath = lambda f : os.path.join(argv[1], f)

#================= correct .project file
os.rename(projpath(".project"), projpath(".project_bak"))
oldProject = open(projpath(".project_bak"), 'r')
newProject = open(projpath(".project"), 'w')

go = lambda : oldProject.readline()
def write_internal(f, l):
    print >> f, l.rstrip()

write = lambda l : write_internal(newProject, l)

l = go()
write(l)
absProjDir = "" # must get it from <location></location> inside <link>
while l:
    l = go()
    if "<linkedResources>" in l:
        while "</linkedResources>" not in l:
            if "<name>[Source directory]</name>" in l:
                write("<name>[Source]</name>")
                l = go() # <type>2</type>
                write(l)
                l = go() # <location>/home/...../cmake</location>
                l = l.strip()[len("<location>"):-len("</location>")]
                absProjDir = os.path.dirname(l)
                write("<location>"+os.path.join(absProjDir, "src")+"</location>")
            else:
                write(l)
            l = go()

        # now l == </linkedResources>, write <name>[GTest]</name> before end
        if addGtest:
            write("<link>\n<name>[Gtest]</name>\n<type>2</type>")
            write("<location>"+os.path.join(absProjDir, "test")+"</location>")
            write("</link>")
        write(l)  #</linkedResources>
        
    else:
        write(l)

newProject.close()
print "New .project written, old one backed up as .project_bak"


#================= correct .cproject file
os.rename(projpath(".cproject"), projpath(".cproject_bak"))
oldCproject = open(projpath(".cproject_bak"), 'r')
newCproject = open(projpath(".cproject"), 'w')

go = lambda : oldCproject.readline()
write = lambda l : write_internal(newCproject, l)

l = go()
write(l)
addOnce = False
while l:
    l = go()
    if "[Source directory]" in l:
        # there are two places. replace them all
        write(l.replace("Source directory", "Source"))
        if not addOnce:
            addOnce = True
            # add [Gtest] as "src"
            write('<pathentry kind="src" path="[Gtest]"/>')
    else:
        write(l)

newCproject.close()
print "New .cproject written, old one backed up as .cproject_bak"