/**************************************************/
//Multiply two 3x3 matrixs. This function developed by Jordi can be easily adapted to multiple n*n matrix's. (Pero me da flojera!). 
void Matrix_Multiply(float a[3][3], float b[3][3],float mat[3][3])
{
  float op[3]; 
  for(int x=0; x<3; x++)
  {
    for(int y=0; y<3; y++)
    {
      for(int w=0; w<3; w++)
      {
       op[w]=a[x][w]*b[w][y];
      } 
      mat[x][y]=0;
      mat[x][y]=op[0]+op[1]+op[2];
      
      float test=mat[x][y];
    }
  }
}

void Matrix_Identity(float mat[3][3]){
  int i=0;
  int j=0;
  
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(i==j)
        mat[i][j]=1;
      else
        mat[i][j]=0;
    }
}
}

void Matrix_Zero(float mat[3][3]){
  int i=0;
  int j=0;
  
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
    mat[i][j]=0;
    }
}
}
