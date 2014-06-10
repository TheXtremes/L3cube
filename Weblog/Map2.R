library(maps)
map()
freegeoip <- function(ip, format = ifelse(length(ip)==1,'list','dataframe'))
{
    if (1 == length(ip))
    {
        # a single IP address
        require(rjson)
        url <- paste(c("http://www.telize.com/geoip/", ip), collapse='')
        ret <- fromJSON(readLines(url, warn=FALSE))
        if (format == 'dataframe')
            ret <- data.frame(t(unlist(ret)))
        return(ret)
    } else {
        ret <- data.frame()
        for (i in 1:length(ip))
        {
            r <- freegeoip(ip[i], format="dataframe")
            ret <- rbind(ret, r)
        }
        return(ret)
    }
}
d <- read.table("weblog2.txt")
types<-factor(d$V1)
for(i in 1:length(levels(types))){
points(freegeoip(levels(types)[i])$longitude,freegeoip(levels(types)[i])$latitude,col=2,pch=4)   
}
