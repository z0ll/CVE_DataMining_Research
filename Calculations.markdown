For each json file, I read out its CWE, CAPEC, Risk severity and CPE value, and store them in an object. 
Then, I creat four category sets, each containing items (unique) from one category, CWE, CAPEC, Risk or CPE. 

Each item in the category set has a file-list that stores the index of the file that contains it. The size of the list correspond to the frequency of that item.

Two Category analysis was done by finding the intersection of the file-lists of two items. The number of elements in the intersection indicates the frequency of those items appearing together.

The lists were output into CSV files unsorted. I sorted the files with MS Office Excel. 

The heatmap is impossible to reproduce, as we do not have exactly the same sequence of CPEs. The author did not use actual CPE IDs, so the order of list matters to how the heat map looks.