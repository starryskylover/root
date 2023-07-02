void lianer_fit(Double_t *a, Double_t *b, Double_t *x, Double_t *y){
Double_t sum_1=0, sum_2=0, sum_3=0, sum_4=0;

for (int i=0; i<3; i++){
  sum_1+=x[i];
  sum_2+=y[i];
  sum_3+=x[i]*y[i];
  sum_4+=x[i]*x[i];
}

  Double_t *a=(3*sum_3-sum_1*sum_2)/(3*sum_4-sum_1*sum_1);
  Double_t *b=(sum_2-(*a)*sum_1)/3;
}

  int main()
  {
  int n = 0;
  Double_t a,b;
   cout << "Введите размерность массива: " << endl;
   cin >> n;
   Double_t *x = new Double_t[n];
   for (int i = 0; i < n; i++)
   {
       cin >> x[i];
   }
   Double_t *y = new Double_t[n];
   for (int j = 0; j < n; j++)
   {
       cin >> y[j];
   }
   leaner_fit(&a,&b,x,y);
   std::cout << "Линейный фит: y(x)=" << a<< "x+"<<b <<'\n';
   return 0;
}
