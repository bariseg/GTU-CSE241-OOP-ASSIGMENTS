--------------------

exit features:
    * exit : you must terminate the OS with "exit" command.
             saves all data and filestrucure to the harddisc/storage.txt and harddisc/fileStructure.txt.
             if there is a problem with saving, throws an exception(will never be caught).
             in case of problem with saving, check readme.txt file to handle the situation.
             
--------------------
commands features:
    * commands : lists all valid commands. Detailed explanation of the commands is in this readme2.txt file.
--------------------

storage features:
    * storage : prints the memory used, memory remain, and maximum memory that OS can use.

--------------------

ls features:
    * ls    : prints the sub-fileentities of the current directory to the screen.
    * ls -R : prints all the sub-fileentities recursively until it reaches the leafs of the file structure

    a file structure for example:

    -home
    -dir1
        -file2
        -dir2
            -copiedFileLinked
        -copiedFile
    -file1
    -file1L

    ls -R output:
        
    home(home/):
    D dir1	Jan 07 19:46	
    F file1	Jan 09 02:01	511 bytes	
    S file1L	Jan 09 02:48	home/file1/
    dir1(home/dir1/):
    F file2	Feb 07 19:47	127 bytes	
    D dir2	Jan 09 14:06	
    F copiedFile	Jan 09 14:13	7423 bytes	
    dir2(home/dir1/dir2/):
    S copiedFileLinked	Jan 09 14:14	home/dir1/copiedFile/

--------------------

cd features:

    * cd mydir : changes the current directory to mydir,
                 if there is a one with that name in the current directory
    * cd home/dir1/dir2/ : changes the current directory to the target directory(dir2) that has the given path,
                           if there exists.
                           cd home/ does nothing, use "cd .." instead.
                           "cd home/dir1/dir2" is an invalid input. All paths end with '/'.
    * cd .     : changes the current directory to the sup-directory of the current directory,
                 if the current directory is not the basedirectory of the OS.
    * cd ..    : changes the current directory to the basedirectory,
                 if the current directory is not the basedirectory of the OS.
    
--------------------

rm features:

    * rm some_name : removes the target file or directory,
                     if there is a one with the name "some_name" in the current directory.
                     (if the target is a directory, it should not have any sub-directories.)

--------------------

link features:

    * link home/dir3/someFile/ link_someFile : creates a softlinkedfile named "link_someFile" in the current directory,
                                               if the given path has a corresponding regularfile in the operating system.
    Note : SoftLinkedFile objects represented by its own name,path,createdTime and the data of the destFile.
           if the dest file has been deleted or corrupted. then data is not reachable. throws exception with a message, does not terminate the OS

--------------------

mkdir features:
    * mkdir dirname : creates a new directory named "dirname" in the current directory.
                      if there is not already one named "dirname"

--------------------

cat features:
    * cat filename : types the file contents on the screen,if there exists
    
    * cat linkedfilename : types the file contents of the sourcefile of the linked file named "linkedfilename", if there exists.

    * cat directoryname filename: if the parameter is a directory, then it takes another argument until the argument is a file
    
    for example: 

        home/
        |-- dir1
        |   |-- file1
        |   |-- dir2
        |       |-- file2

    to reach file2: 
        * cat dir1 dir2 file2 : executes cat command for file2
        * cat dir1 file1 : executes cat command for file1
        * cat dir1 dir2 (this command waits for another parameter)

--------------------

cp features:
    Note : if the first parameter(path) has the char '/' as the last char, then it is searched in the OS being developed by me.
           if the path does have a extention(like ".txt, .cpp, .c") ,and not have '/' as the last char, then it is searched in the OS of the device(UBUNTU)

           the sourcefile must not have a path that has whitescapes in it! unpredictable behaivor will occur.


    * cp home/dir1/file1/ file1copy : copies the file(file1) corresponds the path, to the current directory, and names it "file1copy"
    * cp home/dir1/ dircopy : directory copy is not available yet.
    
    * cp /Users/bariserengezici/Desktop/somedirectory/deneme.txt copiedfile : copies a file from UBUNTU

--------------------