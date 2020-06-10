# 1 Max Flow 最大網路流 
真不愧是北一女[https://www.youtube.com/watch?v=U6SCE4MTC_Q]  
<img src="https://i.imgur.com/HaZY7D4.png" width="600">
<img src="https://i.imgur.com/ezfiRsq.png" width="600">
<img src="https://i.imgur.com/zuwRY4J.png" width="600">
<img src="https://i.imgur.com/967ygZa.png" width="600">

# 2 使用DFS找Component  
```cpp
for(v in Graph){
  if(!mark[v]){
    ++c;
    dfs(v);
  }
}
```
# 3 有負權重和負環的最短路徑
dijkstra窮舉版  
先從與起點連接的node開始，窮舉可走到的所有node組合，再更新dis\[\]  
```cpp
if(dis[j]>dis[i]+map[i][j]){ //如果原本的距離 > 經由i到達的距離
  dis[j]=dis[i]+map[i][j];
}
```
做完一次之後做第二次  
如果距離有變少就代表有負環  
```cpp
if(dis[j]>dis[i]+map[i][j]) return 0; //代表有負環
```
# 網路packet傳送
<img src="https://i.imgur.com/FL5L9aC.png" width="600">   
直接模擬封包傳送      

```cpp
//初始化路徑 (最短路徑)
	for(int i=0;i<deliverNum;++i){
		findShortestPath(deliver[i]-1,i);
	}
	//模擬packet走法，每while一次代表過一秒 
	while(!done()){
		for(int i=0;i<deliverNum;++i){ //所有node都執行動作
			if(!isInTar[i]){ //如果還沒到終點
				if(!isInNode(i)){ 如果不在node的buffer裡
					go(i); //前進
				}
			}
		}
		goBuffer(); //每個node都處理1單位的buffer
	}
	//print tar buffer
	for(int i=qHead[tar+1];i<qTail[tar+1];++i){
		printf("%d ",buffer[tar+1][i]);
	}
```

這是還沒用struct和class所寫的code，超多陣列，可怕==   
# 5
目前有i個componenet   
找出刪掉j個點之後能變成i+j個component的點   
<img src="https://i.imgur.com/75jQVf3.png" width="600">  
直接從排列組合窮舉從刪1個點到刪V個點的組合   
使用[tarjan](https://blog.csdn.net/hurmishine/article/details/75248876)找component   
這科雖說是資料結構，但我完全沒用到資料結構呢==，依舊是一推陣列，可怕    
當初只是想把結果搞出來就行了，沒注意這麼多   


