using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;



namespace calculoCPFCNPJ
{
    class Program
    {
        //StreamReader arquivoTXT;
        static List<string> cpfList, cnpjList, cpfDigitList, cnpjDigitList;
        static Stopwatch cpfTime, cnpjTime, fileReadTime, fullTime;
        static string filePath = string.Format(@"C:\Users\andre\Desktop\BASE.txt"); //Mudar caminho do arquivo de entrada
        static string caminhoDestinoArquivos = string.Format(@"C:\Users\andre\Desktop\"); //Mudar caminho do arquivo de saida
        static StreamWriter sw;

        static void Main(string[] args)
        {
            cpfList = new List<string>();
            cnpjList = new List<string>();
            cpfDigitList = new List<string>();
            cnpjDigitList = new List<string>();
            cpfTime = new Stopwatch();
            cnpjTime = new Stopwatch();
            fileReadTime = new Stopwatch();
            fullTime = new Stopwatch();
            fullTime.Start();

            
            Console.WriteLine("--Inicio Leitura --");
            lerArquivo(filePath);
            Console.WriteLine("--Fim Leitura --");

            Console.WriteLine("--Inicio Calculo --");

            //parte com thread --------------------------------------
            Thread threadCPF = new Thread(new ThreadStart(calcularCPF));
            Thread threadCNPJ = new Thread(new ThreadStart(calcularCNPJ));

            threadCPF.Start();
            threadCNPJ.Start();

            Console.WriteLine("--Thread CPF --");
            threadCPF.Join();
            Console.WriteLine("--Thread CNPJ --");
            threadCNPJ.Join();
            //--------------------------------------------------------

            //parte sem thread (comentar uma e descomentar a outra)
            //Console.WriteLine("--Sem Thread CPF --");
            //calcularCPF();
            //Console.WriteLine("--Sem Thread CNPJ --");
            //calcularCNPJ();
            //--------------------------------------------------------

            Console.WriteLine("--Fim Calculo --");

            Console.WriteLine("--Inicio Escrita --");
            writeFile(caminhoDestinoArquivos, "baseCPF.txt", cpfDigitList);
            writeFile(caminhoDestinoArquivos, "baseCNPJ.txt", cnpjDigitList);
            Console.WriteLine("--Fim Escrita --");

            fullTime.Stop();

            Console.WriteLine(string.Format("Tempo de leitura do arquivo: {0}", fileReadTime.Elapsed));
            Console.WriteLine(string.Format("Tempo do calculo dos cpfs  : {0}", cpfTime.Elapsed));
            Console.WriteLine(string.Format("Tempo do calculo dos cnpjs  : {0}", cnpjTime.Elapsed));
            Console.WriteLine(string.Format("Total Execucao    : {0}", fullTime.Elapsed));
        }

        public static int lerArquivo(string filePath)
        {
            fileReadTime.Start();
            int qtdRegistros = 0;
            StreamReader arquivoTXT = new StreamReader(filePath);
            

            if (File.Exists(filePath))
            {
                using (arquivoTXT)
                {
                    string linha;
                    int count = 0;
                    int countCPF = 0;
                    int countCNPJ = 0;
                    while ((linha = arquivoTXT.ReadLine()) != null)
                    {
                        linha = linha.TrimStart();
                        count++;
                        //Console.WriteLine(linha);
                        if (linha.Length == 9)
                        {
                            countCPF++;
                            cpfList.Add(linha);

                        }
                        else if (linha.Length == 12)
                        {
                            countCNPJ++;
                            cnpjList.Add(linha);
                        }
                    }
                    Console.WriteLine(string.Format("CPF: {0}", countCPF));
                    Console.WriteLine(string.Format("CNPJ: {0}", countCNPJ));
                    Console.WriteLine(string.Format("Total de registros: {0}", count));
                }
            }
            else
            {
                Console.WriteLine("Arquivo não encontrado");
            }

            fileReadTime.Stop();
            return qtdRegistros;
        }

        static void calcularCPF()
        {
            cpfTime.Start();
            int[] multiplicador1 = new int[9] { 10, 9, 8, 7, 6, 5, 4, 3, 2 };
            int[] multiplicador2 = new int[10] { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2 };
            int soma = 0;
            string digito = "";

            foreach (string cpf in cpfList)
            {
                if (cpfList.Count > 0)
                {
                    //for (int j = 0; j < 10; j++) //********
                    //{
                    //    if (j.ToString().PadLeft(11, char.Parse(j.ToString())) == cpf)
                    //    {
                    //        return null;
                    //    }
                    //}

                    //aplica as regras para validação do cpf
                    string tempCpf = cpf.Substring(0, 9);
                    for (int i = 0; i < 9; i++)
                    {
                        //multiplica os numeros pela sequencia decrescente de 10 a 2 e soma tudo 
                        soma += int.Parse(tempCpf[i].ToString()) * multiplicador1[i];
                    }
                    //calcula o resto    
                    int resto = soma % 11;
                    if (resto < 2)
                    {
                        resto = 0;
                    }
                    else
                    {
                        resto = 11 - resto;
                    }
                    digito = resto.ToString();
                    tempCpf = tempCpf + digito;
                    soma = 0;

                    for (int i = 0; i < 10; i++)
                    {
                        soma += int.Parse(tempCpf[i].ToString()) * multiplicador2[i];
                    }

                    resto = soma % 11;
                    if (resto < 2)
                    {
                        resto = 0;
                    }
                    else
                    {
                        resto = 11 - resto;
                    }

                    digito = digito + resto.ToString();
                    string fullCpf = cpf + digito.ToString();
                    cpfDigitList.Add(fullCpf);
                    //Console.WriteLine(string.Format("CPF: {0}", digito));
                }
            }
            
            cpfTime.Stop();
        }


        static void calcularCNPJ()
        {
            cnpjTime.Start();
            int[] multiplicador1 = new int[12] { 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2 };
            int[] multiplicador2 = new int[13] { 6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2 };
            int soma = 0;
            string digito = "";

            foreach (string cnpj in cnpjList)
            {
                if (cnpjList.Count > 0)
                {
                    string tempCnpj = cnpj.Substring(0, 12);
                    soma = 0;

                    for (int i = 0; i < 12; i++)
                    {
                        soma += int.Parse(tempCnpj[i].ToString()) * multiplicador1[i];
                    }

                    int resto = (soma % 11);
                    if (resto < 2)
                    {
                        resto = 0;
                    }
                    else
                    {
                        resto = 11 - resto;
                    }

                    digito = resto.ToString();
                    tempCnpj = tempCnpj + digito;
                    soma = 0;

                    for (int i = 0; i < 13; i++)
                    {
                        soma += int.Parse(tempCnpj[i].ToString()) * multiplicador2[i];
                    }

                    resto = (soma % 11);
                    if (resto < 2)
                    {
                        resto = 0;
                    }
                    else
                    {
                        resto = 11 - resto;
                    }
                    digito = digito + resto.ToString();
                    string fullCnpj = cnpj + digito.ToString();
                    cnpjDigitList.Add(fullCnpj);
                }
            }

            cnpjTime.Stop();
        }

        static void writeFile(string caminhoSaida, string nomeArquivo, List<String> lista)
        {
            
            using (sw = new StreamWriter(string.Concat(caminhoSaida, nomeArquivo)))
            {
                foreach (string item in lista)
                {
                    sw.WriteLine(item);
                }
            }
            sw.Close();
        }
    }
}




