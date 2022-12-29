# In order to run this script, open a Terminal session
# to the same directory and type "chmod u+x comprun.sh"
# without the quotes once to update permissions. Then to
# run the script, from the same Terminal type "./comprun.sh"

# exit script at first error
set -u -e

# compile it and output to executable called app
g++ ./src/*.cpp -std=c++17 ./lib/SelbaWard/*.cpp -o main -F/Library/Frameworks -I/Library/Frameworks/SFML.framework/Headers -framework sfml-graphics -framework sfml-window -framework sfml-system -I./headers -I./lib

# run the app
./main