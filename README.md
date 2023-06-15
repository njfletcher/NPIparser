# NPIparser

Parses NPI(National Provider Identifier) files and creates a new file that contains rows that match any of the zipcodes in the zipcodes.csv file. This takes about 4 minutes to run on a 10gb file.

To use: 
1)download and make.
2)./parser.exe [inputfile]. Note: this program expects the input file and zipcode file to be in the same directory as the source.
3)This will create an output file named "outputinputfile" that will be a parsed version.
