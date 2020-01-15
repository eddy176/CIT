config enable_prompt 0

#
# try to solve one cube using depth limited search
#

echo Trying to solve this cube
show cube
search tree dl
echo

echo Resulting cube is
show cube
echo

echo Was it solved?
equal solved
