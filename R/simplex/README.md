The **simplex** folder stores R scripts to draw  
points from a proportion simplex for functional  
analyses of categorical distributions and  
composition data likelihoods.  
  
*  **mk-simplex.r** outputs uniform grid of simplex samples to a csv-format file  
   based on the based on the set of K-compositions of an integer,  
   where a closed simplex includes the boundary with one or more zero proportions  
   and an open simplex excludes the boundary with all proportions positive   
*  **mk-simplex-dirichlet.r** outputs random samples from a normalized  
   Dirichlet distribution to a csv-format file using MCMCpack()  
*  **mk-simplex-dirichlet-rgamma.r** outputs random samples from a  
   Dirichlet distribution to a csv-format file using rgamma()  
*  **mk-simplex-normalized-uniform.r** outputs random samples from a  
   normalized uniform cube density to a csv-format file  
*  **nexcom.r** outputs a data frame containing the set   
   of K compositions of an integer N  
*  the folder **examples** stores some examples of simplexes   
   and some initial versions of R scripts to generate simplex samples

Jon Brodziak, PIFSC, jon.brodziak@noaa.gov
