#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
// #include <lua.h>
// #include <lualib.h>
// #include <lauxlib.h>
#include <string.h>
#include <ctype.h>

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = *(array) + count; keep; keep = !keep)

// readfile
// char *readfile(char *filename) {
int readfile(lua_State *L) {
    const char * filename = lua_tostring(L, -1);    // get the filename
    // get the size of the file
    struct stat info;                   // initialize stat and info structs
    int status = stat(filename, &info); // status = return of stat (ignore)
    if (status < 0) {
        perror("stat error");
        exit(1);
    }
    // get a buffer of the appropriate size
    int size = (int) info.st_size;
    char *buffer = malloc(size + 1); // set up buffer size wide
    if (buffer == NULL) {
        perror("buffer error");
	exit(1);
    }
    // open the file
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }   // file is empty or doesn't exist
    // read the entire file
    char *ptr = buffer;             // ptr is a pointer to the buffer beginning
    int left = size;                // left is the size to be indexed
    while (left > 0) {              // for what is left of the file
        int chunk = read(fd, ptr, left);    // grabs chunk size of next word
        if (chunk < 0) {
            perror("read error");
            exit(1);
        } else if (chunk == 0) {
            fprintf(stderr, "ran out of data\n");
            exit(1);
        }   // finished file
        left -= chunk;      // -chunk to input
        ptr += chunk;       // +chunk to buffer
    }   // once left has nothing in it
    // terminate the string with a null
    *ptr = 0;   // ptr = 0
    // close the file
    status = close(fd); // closes the file
    if (status < 0) {
        perror("close error");
        exit(1);
    }
    lua_pushstring(L, ptr);
    return 1;
}

int tokenize(lua_State *L) {
    const char *buffer = luaL_checkstring(L, 1);
    int buffer_size = strlen(buffer);
    int offset = luaL_checkinteger(L, 2);
    int first = 0;
    int size = 0;
    while (first < buffer_size && isspace(buffer[first])) {
        first += 1;
    }
    int end = first;
    while (end < buffer_size && !isspace(buffer[first])){
        end += 1;
        size += 1;
    }
    char* raw;
    char* new_token = malloc(size + 1);
    char* token;
    char* var;
    foreach(int cha, raw) {
        if (isalnum((int)cha)) {
            token += tolower(cha);
        }
    }
    lua_pushstring(L, token);
    lua_pushinteger(L, end);

    return 1; // here's a token and where it left off
}

// argc is # of cmd args, argv is an array of arguments
int main(int argc, char *argv[]) {
    char* filename;
    int grams = 3;
    int wordcount = 100;

    // check command line args
    if (argc != 3 && argc != 4) {   // if not enough args
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);                // throw an error, show usage
    }
    if (argc == 4) {
        grams = atoi(argv[3]);
    }
    filename = argv[1];
    wordcount = atoi(argv[2]);

    lua_State *L = luaL_newstate(); // create a new lua env L
    luaL_openlibs(L);

    lua_register(L, "creadfile", readfile);     // register readfile to lua
    lua_register(L, "ctokenize", tokenize);   // register parsefile

    if (luaL_dofile(L, "babbler.lua")) {     // if luaBabbler returns failure
        printf("Error in dofile!\n");
        return 1;
    }
    lua_getglobal(L, "bab");    // returns the value from bab in lua file

    lua_pushstring(L, filename);
    lua_pushnumber(L, wordcount);
    lua_pushnumber(L, grams);
    // this will call whatever function that is on the stack, passing in however many variables after it.
    lua_pcall(L, 3, 1, 0);    // (L, number of variables sending, recieving, testfx)
    
	lua_pushcfunction(L, readfile);
	lua_setglobal(L, "readfile");
	lua_pushcfunction(L, tokenize);
	lua_setglobal(L, "ctokenize");
    lua_close(L);

    return 0;
}

