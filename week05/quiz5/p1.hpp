const int size=10;

void sort(int arr[]){
	//add here
	int tmp;
	for(int a=0;a<size;a++){
		for(int b=0;b<a;b++){
			if((arr[a]<0?(-1)*arr[a]:arr[a])%2==0){
				if((arr[b]<0?(-1)*arr[b]:arr[b])%2==0&&(arr[b]<arr[a])){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;		
				}else if((arr[b]<0?(-1)*arr[b]:arr[b])%2==1){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;
				}
			}else{
				if((arr[b]<0?(-1)*arr[b]:arr[b])%2==1&&(arr[b]<arr[a])){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;
				}
			}
		}
	}
}
