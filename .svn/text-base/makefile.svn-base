#----------------------------------------------------------------------------
# Author: Nathan Hansen, Cody Foltz, Nathan Anderson, Eric Olson
# Date: Febuary 9th 2012
#----------------------------------------------------------------------------

#
# First declare aliases for use later on
#

CC              = g++
#			Commented out because of the curl lib >.> the header files are located at /include/curl/curl.h we should use those.
CFLAGS          = -g -Wall #-pedantic
CPPFLAGS        = $(CFLAGS)
LIBS            =  -L./libcurl.so # -lcurl
#The Header only files
headerFiles        = BST.h HashMap.h LinkedHashEntry.h 
#The .o files
oFiles             =  cJSON.o crawler.o reviewer.o dictionary.o page_stats.o html_helpers.o program_options.o page_handler.o results_manager.o results_printer.o FileReader.o

################################################################
# ALL
#
# When you run make by itself it will call the crawler config.
#
################################################################
all: crawler
	
crawler: $(headerFiles) $(oFiles)
	$(CC) $(CFLAGS) -o $@ main.C $(oFiles) $(LIBS)
#       g++ -g -Wall -pedantic -o constructor_main constructor_main.C constructor_class.o
clean:
	rm -rf *.o circular_classes constructor_main
	
#Define the O files
cJSON.o: cJSON.h cJSON.c
FileReader.o: FileReader.C FileReader.h
crawler.o: crawler.C crawler.h
dictionary.o: dictionary.C dictionary.h
html_helpers.o: html_helpers.C html_helpers.h
program_options.o: program_options.C program_options.h
results_manager.o: results_manager.C results_manager.h
results_printer.o: results_printer.C results_printer.h
page_handler.o: page_handler.h page_handler.C
page_stats.o: page_stats.C page_stats.h
reviewer.o: reviewer.C reviewer.h