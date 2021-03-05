### Praca projektowa nr 2
### Rozwiązanie zadan
### Imie Nazwisko nr_indeksu kierunek (wybierz: MAT, MAD, IAD)

library("sqldf")
library("dplyr")
library("data.table")
library("tidyr")

Tags <- read.csv("Tags.csv")
Badges <- read.csv("Badges.csv")
Comments <- read.csv("Comments.csv")
Posts <- read.csv("Posts.csv")
Users <- read.csv("Users.csv")
Votes <- read.csv("Votes.csv")
PostLinks <- read.csv("PostLinks.csv")


##------------ ZAD1 ------------

##------- SQL --------

df_sql_1 <- function(Posts)
  {
  sqldf("SELECT Title, Score, ViewCount, FavoriteCount FROM Posts
        WHERE PostTypeId =1 AND FavoriteCount >= 25 AND ViewCount >= 10000")
}

##-------- BASE --------

df_base_1 <- function(Posts)
  {
  finalFrame <- na.omit(Posts[Posts$PostTypeId == 1 & Posts$FavoriteCount >= 25 & Posts$ViewCount >= 10000,
               c("Title", "Score", "ViewCount", "FavoriteCount"),
               drop = FALSE]) 
  rownames(finalFrame) <- NULL
  finalFrame
}

##-------- DPLYR --------

df_dplyr_1 <- function(Posts)
  {
  finalFrame <- 
    Posts %>% filter(PostTypeId == 1 & FavoriteCount >= 25 & ViewCount >= 10000) %>% 
    select("Title", "Score", "ViewCount", "FavoriteCount")
  finalFrame
}

##-------- DATA.TABLE --------

df_table_1 <- function(Posts)
  {
  posts <- as.data.table(Posts)
  finalFrame <- posts[PostTypeId == 1 & FavoriteCount >= 25 & ViewCount >= 10000,
                      list( Title, Score, ViewCount, FavoriteCount)]
  finalFrame
}

##------------ ZAD2 ------------

##------- SQL --------

df_sql_2 <- function(Tags, Posts, Users)
  {
  sqldf("SELECT Tags.TagName, Tags.Count, Posts.OwnerUserId, Users.Age, Users.Location, Users.DisplayName
       FROM Tags
       JOIN Posts ON Posts.Id=Tags.WikiPostId
       JOIN Users ON Users.AccountId=Posts.OwnerUserId WHERE OwnerUserId != -1
       ORDER BY Count DESC") 
}

##-------- BASE --------

df_base_2 <- function(Tags, Posts, Users)
  {

  halfOfFrame <- merge(x = Tags , y = Posts, 
           by.x="WikiPostId", by.y="Id")

  wholeFrame <- merge(x = halfOfFrame, y = Users,
           by.x = "OwnerUserId", by.y = "AccountId")
  wholeFrame  <- wholeFrame [wholeFrame$OwnerUserId != -1, 
              c("TagName", "Count", "OwnerUserId", "Age", "Location", "DisplayName")]
  wholeFrame  <- wholeFrame [order(wholeFrame$Count, decreasing = TRUE), ]

  row.names(wholeFrame) <- NULL

  indexOfNa <- which(is.na(wholeFrame))
  finalFrame <- wholeFrame[-indexOfNa,]
  finalFrame
}

##-------- DPLYR --------

df_dplyr_2 <- function(Tags, Posts, Users)
  {
  halfOfFrame <- inner_join(Posts, Tags, by = c("Id"= "WikiPostId")) %>% 
    mutate(OwnerUserId1 = OwnerUserId)
  
  finalFrame <- inner_join(Users, halfOfFrame, by = c("AccountId"= "OwnerUserId1")) %>% 
    filter(OwnerUserId != -1) %>% arrange(desc(Count)) %>% 
    select("TagName", "Count", "OwnerUserId", "Age", "Location", "DisplayName")
  
  finalFrame
}

##-------- DATA.TABLE --------

df_table_2 <- function(Tags, Posts, Users)
  {
  tags <- as.data.table(Tags)
  posts <- as.data.table(Posts)
  user <- as.data.table(Users)

  setkey(tags , WikiPostId)
  setkey(posts , Id)

  halfOfFrame <- tags[posts, on = c("WikiPostId" ="Id") , nomatch=0]
  wholeFrame <- halfOfFrame[OwnerUserId != - 1]
  setkey(wholeFrame , OwnerUserId)
  setkey(user , AccountId)

  finalFrame <- wholeFrame[user, on = c("OwnerUserId" = "AccountId"), nomatch = 0]
  
  finalFrame <- finalFrame[,list(TagName, Count, OwnerUserId, Age, Location,  DisplayName)]
  finalFrame
}

##------------ ZAD3 ------------

##------- SQL --------

df_sql_3 <- function(PostLinks, Posts)
  {
  sqldf("SELECT Posts.Title, RelatedTab.NumLinks 
       FROM
       (SELECT RelatedPostId AS PostId, COUNT(*) AS NumLinks 
       FROM PostLinks GROUP BY RelatedPostId) AS RelatedTab
       JOIN Posts ON RelatedTab.PostId=Posts.Id WHERE Posts.PostTypeId=1
       ORDER BY NumLinks DESC") 
}

##-------- BASE --------

df_base_3 <- function(PostLinks, Posts)
  {
  RelatedTab <- aggregate(x = PostLinks$RelatedPostId, 
                        by = PostLinks["RelatedPostId"], FUN = length)

  colnames(RelatedTab) <- c("PostId", "NumLinks")

  postsPart <- Posts[Posts$PostTypeId ==1 ,c("Title","PostTypeId", "Id")]

  finalFrame <- merge(x = RelatedTab, y = postsPart,
           by.x = "PostId", by.y = "Id")

  finalFrame <- finalFrame[order(finalFrame$NumLinks, decreasing = TRUE), ]
  finalFrame <- finalFrame[c("Title", "NumLinks")]
  finalFrame
}

##-------- DPLYR --------

df_dplyr_3 <- function(PostLinks, Posts)
  {
  RelatedTab <- PostLinks %>% select("RelatedPostId") 

  RelatedTab <- RelatedTab %>% group_by(RelatedPostId ) %>% 
    summarise(NumLinks = length(RelatedPostId)) %>% 
    rename(PostId = RelatedPostId)

  halfOfFrame <- Posts %>% filter(PostTypeId == 1) 
  finalFrame <- inner_join(RelatedTab, halfOfFrame, by = c("PostId"= "Id")) %>% 
    arrange(desc(NumLinks)) %>% select("Title", "NumLinks")
  finalFrame
}

##-------- DATA.TABLE --------

df_table_3 <- function(PostLinks, Posts){
  postlinks <- as.data.table(PostLinks)
  posts <- as.data.table(Posts)

  RelatedTab <- postlinks[, .(NumLinks = .N), by = RelatedPostId][order(RelatedPostId)]

  setnames(RelatedTab,  c("PostId", "NumLinks"))

  setkey(RelatedTab, PostId)
  setkey(posts, Id)

  halfOfFrame <- posts[PostTypeId == 1]

  finalFrame <- RelatedTab[halfOfFrame, on = c("PostId" = "Id"), nomatch=0][order(-NumLinks)]

  finalFrame <- finalFrame[, list(Title, NumLinks)]
  finalFrame
}

##------------ ZAD14------------

##------- SQL --------

df_sql_4 <- function(Users, Badges)
  {
  sqldf("SELECT DISTINCT Users.Id, Users.DisplayName, Users.Reputation, Users.Age, Users.Location
       FROM (
       SELECT
       Name, UserID FROM Badges
       WHERE Name IN ( SELECT
       Name FROM Badges
       WHERE Class=1
       GROUP BY Name
       HAVING COUNT(*) BETWEEN 2 AND 10
       )
       AND Class=1
       ) AS ValuableBadges
       JOIN Users ON ValuableBadges.UserId=Users.Id")
}

##-------- BASE --------

df_base_4 <- function(Users, Badges)
  {
  firstFrame <- Badges[Badges$Class == 1, "Name", drop = FALSE]
  numbers <- aggregate(x = firstFrame$Name, by = firstFrame["Name"], FUN = length)

  wholeFirstFrame <- numbers[(numbers$x >= 2  & numbers$x <= 10), ]
  rownames(wholeFirstFrame) <- NULL
  wholeFirstFrame <- wholeFirstFrame["Name"]
  colnames(wholeFirstFrame) <- NULL

  wholeFirstFrame <- lapply(wholeFirstFrame, as.character)
  rowWithCharackter <- as.vector(wholeFirstFrame)
  
  ValuableBadges <- Badges[ Badges$Class == 1 & Badges$Name %in% rowWithCharackter[[1]], c("Name", "UserId") ]

  user <- unique(Users[, c ("Id", "DisplayName", "Reputation", "Age", "Location")])
  ValuableBadges <- unique(ValuableBadges[,"UserId", drop = FALSE])
  rownames(ValuableBadges) <- NULL

  finalFrame <- merge(x = user, y = ValuableBadges,
           by.x = "Id", by.y = "UserId")
  finalFrame
}

##-------- DPLYR --------

df_dplyr_4 <- function(Users, Badges)
  {
  firstFrame <- Badges %>% filter(Class == 1) %>% select(Name) %>% group_by(Name) %>% summarise(COUNT = length(Name)) %>% 
  filter(COUNT >=2 & COUNT <= 10)

  firstFrame <- firstFrame %>% pull(Name)
  ValuableBadges <- Badges %>% filter(Class == 1 & Name %in% firstFrame) %>% select("Name" , "UserId")

  wholeFrame <- Users %>% mutate(Id1 =Id)

  finalFrame <- inner_join(ValuableBadges, wholeFrame, by= c("UserId"="Id1")) %>% select("Id", "DisplayName", "Reputation", "Age", "Location") 

  finalFrame <-  distinct(finalFrame)
  finalFrame
}

##-------- DATA.TABLE --------

df_table_4 <- function(Users, Badges)
  {
  badges <- as.data.table(Badges)
  user <- as.data.table(Users)

  ValuableBadges <- badges[Class == 1, .(COUNT = .N) ,by = Name][COUNT >= 2 & COUNT <= 10]
  ValuableBadges <- badges[Class == 1 & Name %in% ValuableBadges[[1]]][,list(Name, UserId)]

  setkey(ValuableBadges, UserId)
  setkey(user, Id)

  finalFrame <- unique(ValuableBadges[user, nomatch = 0,
                                      .(Id, DisplayName, Reputation, Age, Location)])[order(Id)]

  finalFrame
}

##------------ ZAD5 ------------

##------- SQL --------

df_sql_5 <- function(Votes)
  {
  sqldf("SELECT UpVotesTab.PostId, UpVotesTab.UpVotes, IFNULL(DownVotesTab.DownVotes, 0) AS DownVot FROM
       (
       SELECT PostId, COUNT(*) AS UpVotes FROM Votes
       WHERE VoteTypeId=2 GROUP BY PostId ) AS UpVotesTab
       LEFT JOIN
       (
       SELECT PostId, COUNT(*) AS DownVotes FROM Votes
       WHERE VoteTypeId=3 GROUP BY PostId ) AS DownVotesTab
       ON UpVotesTab.PostId=DownVotesTab.PostId") 
}

##-------- BASE --------

df_base_5 <- function(Votes)
  {
  helpFrame1 <- Votes[Votes$VoteTypeId == 2, ]

  UpVotesTab <- aggregate(x = helpFrame1$PostId, by = helpFrame1["PostId"], FUN = length)
  colnames(UpVotesTab) <- c("PostId", "UpVotes")

  helpFrame2 <- Votes[Votes$VoteTypeId == 3, ]
  DownVotesTab <- aggregate(x = helpFrame2$PostId, by = helpFrame2["PostId"], FUN = length)
  colnames(DownVotesTab) <- c("PostId", "DownVotes")

  finalFrame <- merge(x = UpVotesTab, y = DownVotesTab,
           by.x = "PostId", by.y = "PostId",
           all.x = TRUE)
  colnames(finalFrame) <- c("PostId", "UpVotes", "DownVot") 
  IndexWhereNa <- which(is.na(finalFrame[, "DownVot"]))
  finalFrame[IndexWhereNa,"DownVot" ] <- 0L
  finalFrame
}

##-------- DPLYR --------

df_dplyr_5 <- function(Votes)
  {
  UpVotesTab <- Votes %>% filter(VoteTypeId == 2) %>% group_by(PostId) %>% 
    select("PostId") %>% summarise(UpVotes = length(PostId))
  DownVotesTab <- Votes %>% filter(VoteTypeId == 3) %>% group_by(PostId) %>% 
    select("PostId") %>% summarise(DownVotes = length(PostId))

  finalFrame <- left_join(UpVotesTab, DownVotesTab, by = "PostId") %>% 
    mutate(DownVot = replace_na(DownVotes, (0L))) %>% select("PostId", "UpVotes", "DownVot")
  finalFrame
}

##-------- DATA.TABLE --------

df_table_5 <- function(Votes)
  {
  votes <- as.data.table(Votes)

  UpVotesTab <- votes[VoteTypeId == 2, .(UpVotes = .N), by = PostId][order(PostId)]
  DownVotesTab <- votes[VoteTypeId == 3, .(DownVotes = .N), by = PostId][order(PostId)]

  finalFrame <- DownVotesTab[UpVotesTab, on ="PostId"]
  finalFrame <- finalFrame[, .(DownVot= replace_na(DownVotes, (0L))), by = c("PostId", "UpVotes")]
  
  finalFrame
}

##------------ ZAD6------------

##------- SQL --------

df_sql_6 <- function(Votes)
  {
  sqldf("SELECT PostId, UpVotes-DownVotes AS Votes FROM (
      SELECT UpVotesTab.PostId, UpVotesTab.UpVotes, IFNULL(DownVotesTab.DownVotes, 0)
      AS DownVotes
      FROM
        (SELECT PostId, COUNT(*) AS UpVotes FROM Votes
            WHERE VoteTypeId = 2 GROUP BY PostId
      ) AS UpVotesTab
      LEFT JOIN
      (SELECT PostId, COUNT(*) AS DownVotes
          FROM Votes WHERE VoteTypeId = 3 GROUP BY PostId
      ) AS DownVotesTab
      ON UpVotesTab.PostId = DownVotesTab.PostId
      
      UNION
      
      SELECT DownVotesTab.PostId, IFNULL(UpVotesTab.UpVotes, 0) AS UpVotes, DownVotesTab.DownVotes
        FROM
          (
      SELECT PostId, COUNT(*) AS DownVotes FROM Votes
          WHERE VoteTypeId = 3 GROUP BY PostId
      ) AS DownVotesTab
      LEFT JOIN
        (
          SELECT PostId, COUNT(*) AS UpVotes FROM Votes
            WHERE VoteTypeId = 2 GROUP BY PostId
      ) AS UpVotesTab
      ON DownVotesTab.PostId = UpVOtesTab.PostId
      )") 
}

##-------- BASE --------

df_base_6 <- function(Votes)
  {
  firstPartOfFrame <- df_base_5(Votes)
  colnames(firstPartOfFrame) <- c("PostId", "UpVotes", "DownVotes")

  helpFrame1 <- Votes[Votes$VoteTypeId == 2, ]

  UpVotesTab <- aggregate(x = helpFrame1$PostId, by = helpFrame1["PostId"], FUN = length)
  colnames(UpVotesTab) <- c("PostId", "UpVotes")

  helpFrame2 <- Votes[Votes$VoteTypeId == 3, ]
  DownVotesTab <- aggregate(x = helpFrame2$PostId, by = helpFrame2["PostId"], FUN = length)
  colnames(DownVotesTab) <- c("PostId", "DownVotes")

  secondPartOfFrame <- merge(x =DownVotesTab , y = UpVotesTab,
           by.x = "PostId", by.y = "PostId",
           all.x = TRUE)

  indexWhereNa <- which(is.na(secondPartOfFrame[, "UpVotes"]))
  secondPartOfFrame[indexWhereNa,"UpVotes" ] <- 0L

  wholeFrame <- unique(rbind(firstPartOfFrame, secondPartOfFrame ))

  finalFrame <- cbind(wholeFrame["PostId"], (wholeFrame["UpVotes"] - wholeFrame["DownVotes"]))
  colnames(finalFrame) <- c("PostId", "Votes")
  finalFrame
}

##-------- DPLYR --------

df_dplyr_6 <- function(Votes)
  {
UpVotesTab <- Votes %>% filter(VoteTypeId == 2) %>% group_by(PostId) %>% 
  select("PostId") %>% summarise(UpVotes = length(PostId))
DownVotesTab <- Votes %>% filter(VoteTypeId == 3) %>% group_by(PostId) %>% 
  select("PostId") %>% summarise(DownVotes = length(PostId))

firstPartOfFrame <- left_join(UpVotesTab, DownVotesTab, by = "PostId") %>% 
  mutate(DownVotes = replace_na(DownVotes, (0L))) %>% select("PostId", "UpVotes", "DownVotes")

secondPartOfFrame <- left_join(DownVotesTab, UpVotesTab, by = "PostId") %>% 
  mutate(UpVotes = replace_na(UpVotes, (0L))) %>% select("PostId", "UpVotes", "DownVotes")

finalFrame <- union(firstPartOfFrame, secondPartOfFrame) %>% 
  mutate(Votes = UpVotes - DownVotes) %>% select("PostId", "Votes")
finalFrame
}

##-------- DATA.TABLE --------

df_table_6 <- function(Votes)
  {
  votes <- as.data.table(Votes)
  
  UpVotesTab <- votes[VoteTypeId == 2, .(UpVotes = .N), by = PostId][order(PostId)]
  DownVotesTab <- votes[VoteTypeId == 3, .(DownVotes = .N), by = PostId][order(PostId)]

  firstPartOfFrame <- DownVotesTab[UpVotesTab, on ="PostId"]
  firstPartOfFrame <- firstPartOfFrame[, .(DownVotes= replace_na(DownVotes, (0L))), 
                                       by = c("PostId", "UpVotes")]

  secondPartOfFrame <- UpVotesTab[DownVotesTab, on = "PostId"]
  secondPartOfFrame <- secondPartOfFrame[, .(UpVotes= replace_na(UpVotes, (0L))), 
                                         by = c("PostId", "DownVotes")]
  secondPartOfFrame <-setcolorder(secondPartOfFrame, c("PostId", "UpVotes", "DownVotes"))

  finalFrame <- funion(firstPartOfFrame, secondPartOfFrame, all = FALSE)
  finalFrame <- finalFrame[, .(Votes = (UpVotes - DownVotes)), by= PostId]
  finalFrame
}




