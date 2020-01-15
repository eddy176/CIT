# use:
# this is for creating a cmd file to use for statistical analysis
# of the rubiks cube solver

def main():
    configfile = "config.cmd"
    searchfile = "search.cmd"
    init_cubes_file = "initcubes.cmd"
    outputfile = "assignment3.cmd"

    # this is where all of the customization for the search is
    config_fin = open(configfile, 'r')

    # put the search configuration in this file
    search_fin = open(searchfile, 'r')

    # this is a file with 100 init cubes are stored 
    init_cubes_fin = open(init_cubes_file, 'r')

    string_to_be_written = ""
    search_string = ""

    # add the configuration to the string
    for line in config_fin:
        line = line.strip()
        string_to_be_written += line + '\n'

    # put the custom search in the search_string
    for line in search_fin:
        line = line.strip()
        search_string += line

    # get the init cubes, add them to the string followed by running the search
    for line in init_cubes_fin:
        line = line.strip()
        string_to_be_written += line + '\n' + search_string + '\n'

    # close all fin files
    config_fin.close()
    search_fin.close()
    init_cubes_fin.close()

    # create the new file and write the string to the new file
    fout = open(outputfile, 'w')
    fout.write(string_to_be_written)

    # close the written file
    fout.close()
    print(outputfile + " file created.")
main()