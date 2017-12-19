#include<stdio.h>

char outtoken[200][50]; //token格納用配列
FILE *fi;
int check_word(char);

int main()
{
	int i,j,token_num;
	char c;
	fi=fopen("tzk1.txt","r");
	token_num=0;  //トークンの数の初期化
	j=0;
	while(1){
		c=fgetc(fi);  //1文字ずつ入力
		printf("%c\n",c);
		if(c==EOF)break;

		if(check_word(c)==0){//数字なら 
			if(j!=0){
				outtoken[token_num][j]=c;
				j++;
			}else{
				outtoken[token_num][0]=c;
				c=fgetc(fi);
				if(c>='0' && c<='9'){
					fseek(fi,-1,1);   //ファイルポインタを1つ戻す 
				}
				else{
					outtoken[token_num][1]='\0';
					token_num++;
					fseek(fi,-1,1);   //ファイルポインタを1つ戻す 
				}
			}
		}

				 
				else if(check_word(c)==1){//文字なら 
			outtoken[token_num][j]=c;
			j++;
		}
		else if(check_word(c)==2){  //改行，スペース，タブなら
				if(j!=0){
					outtoken[token_num][j]='\0';
					j=0;
					token_num++;
				}
			
		}else if(check_word(c)==3){  //記号なら(1文字)
				if(j!=0){
				outtoken[token_num][j]='\0';
				j=0;
				token_num++;
				outtoken[token_num][0]=c;
				outtoken[token_num][1]='\0';
				token_num++;
				}else{
				outtoken[token_num][0]=c;
				outtoken[token_num][1]='\0';
				token_num++;
				}
		 }else if(check_word(c)==4){  //記号なら(2文字)
				if(j!=0){
				outtoken[token_num][j]='\0';
				token_num++;
				j=0;
				outtoken[token_num][0]=c;
				outtoken[token_num][1]=fgetc(fi);
				outtoken[token_num][2]='\0';
				token_num++;
				}else{
				outtoken[token_num][0]=c;
				outtoken[token_num][1]=fgetc(fi);
				outtoken[token_num][2]='\0';
				token_num++;
				}

		}
	
	}
	
	for(i=0;i<token_num;i++)
		printf("%3d  %s\n",i,outtoken[i]);
	return 0;
}

int check_word(char c)
{
	if(c>='0' && c<='9') // 数字なら 
		return 0;
	else if(c>='a'&&c<='z')        //アルファベット
		return 1;
	else if(c=='\n' || c==' '|| c=='\t')        //改行，スペース，タブ
		return 2;
	else if(c=='+'||c=='-'||c=='*'||c=='('||c==')'||c=='='||c==','||c=='.'||c==';'||c=='/')        //1文字のみの記号
		return 3;
	else if(c==':')      //コロンは'='と必ず一緒になる
		return 4;
	else if(c=='<' || c=='>'){  //この場合は次の文字を見る必要がある
		c=fgetc(fi);
		fseek(fi,-1,1);   //ファイルポインタを1つ戻す 
		if(c=='=' || c=='>'){
			return 4;
		}else{
			return 3;
		}
	}
}


