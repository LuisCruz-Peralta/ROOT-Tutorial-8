void Tutorial8(){
TH1F *hist= new TH1F("hist","Histogram",100,0,10);
  
  TRandom2 *rand = new TRandom2(3);
  
  fstream file;
  file.open("data.txt",ios::out); //Introducimos numeros aleatorios al .txt
  
  for (int i =0; i<1000; i++){
  
     double r = rand->Gaus(5,1); //Datos con distribucion gaussiana y dando los parametros mu y sigma 
     file << r << endl;
  }
  file.close();
  file.open("data.txt",ios::in);
  
  double value;
  
  while(1) //leer cada uno de los datos del .txt en un ciclo while
  {
      file >> value;
      hist->Fill(value);
      if(file.eof()) break ;
  };
  file.close();
  hist->GetXaxis()->SetTitle("Distribution");
  hist->GetYaxis()->SetTitle("Entries");
  
  TF1 *fit = new TF1("fit","gaus",0,10); //Para no tener que usar la funcion en el graficador. Se puede poner un rango
  
  fit->SetParameter(0,40); //Se pueden poner parametros para el ajuste del histograma, para casos mas complicados
  fit->SetParameter(1,5);
  fit->SetParameter(2,1);
  
  TCanvas *c1 = new TCanvas();
  hist->SetStats(0); //Se quita la desviacion y media en la grafica
  hist->Draw();
  hist->Fit("fit","Q"); //Se aplica la nueva funcion, la Q hace que no haya numeros en la terminal
  
  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9); //Se coloca una leyenda donde indica cual es el ajuste
  leg->AddEntry(hist,"Measured Data","l");
  leg->AddEntry(fit,"Fit Function","l");
  leg->Draw();
  
  double mean = fit->GetParameter(1);
  double sigma = fit->GetParameter(2);
  
  cout<<mean/sigma << endl;
}
