d <- read.table("weblog1.txt",sep="\t",col.names=c("Status","Bytes"),fill=TRUE)
types <- factor(d$Status)
k <- length(levels(types))
a<-c(0)
for(i in 1:k){
   a[i]<-length(which(d$Status==levels(types)[i]))
}
barplot(a,names.arg=c(levels(types)),xlab="HTTP STATUS CODE",ylab="FREQUENCY")

