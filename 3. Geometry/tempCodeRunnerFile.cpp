	do{
		first[counter] = next;		
		findCenter(inData, base, first[0], first[1], first[2]);
		if(base == comp){
			first.push_back(old);
			break;
		}
		first[counter] = old;
		counter++;
		if(counter>2){
			counter = 0;
			next++;
		}				
		old = first[counter];		
	} while(true);