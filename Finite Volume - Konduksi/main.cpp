#include <iostream>
#include <iomanip>
#include <fstream>

int main()
{
  int jum_baris, jum_kolom, jum_baris_input, jum_kolom_input;
  float K, rho_C;
  float delta_x, delta_y;
  float batas_kiri, batas_kanan, batas_atas, batas_bawah, kondisi_awal;
  float tot_waktu, step_waktu;
  int iterasi;

  std::cout << "//////////////////////";
  std::cout << "SIMULASI PERPINDAHAN KALOR 2D FINITE VOLUME METHOD";
  std::cout << "//////////////////////";
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "**Properti Material**";
  std::cout << std::endl;
  std::cout << "Input Konduktifitas Thermal (W/m.K): ";
  //std::cin >> K;
  K = 10;
  std::cout << "Input Kapasitas Kalor Area (J/m^2.K): ";
  //std::cin >> rho_C;
  rho_C = 10000000;

  std::cout << std::endl;
  std::cout << "**Grid**";
  std::cout << std::endl;
  std::cout << "Input Delta X Sel (m): ";
  //std::cin >> delta_x;
  delta_x = 1e-2;
  std::cout << "Input Delta Y Sel (m): ";
  //std::cin >> delta_y;
  delta_y = 1e-2;
  std::cout << "Input jumlah Baris Matriks: ";
  //std::cin >> jum_baris_input;
  jum_baris_input = 10;
    if (jum_baris_input < 4)
    {
        std::cout << "Jumlah Baris Terlalu Kecil";
        return 0;
    }
  std::cout << "Input jumlah Kolom Matriks: ";
  //std::cin >> jum_kolom_input;
  jum_kolom_input = 10;
    if (jum_kolom_input < 4)
    {
        std::cout << "Jumlah Kolom Terlalu Kecil";
        return 0;
    }
  std::cout << "Ukuran Panjang Domain : " << (delta_x * jum_kolom_input) << " m" <<std::endl;
  std::cout << "Ukuran Lebar Domain : " << (delta_y * jum_baris_input) << " m" <<std::endl;

  std::cout << std::endl;
  std::cout << "**Kondisi Batas**";
  std::cout << std::endl;
  std::cout << "Input Nilai Batas Kiri (K): ";
  //std::cin >> batas_kiri;
  batas_kiri = 50;
  std::cout << "Input Nilai Batas Kanan (K): ";
  //std::cin >> batas_kanan;
  batas_kanan = 75;
  std::cout << "Input Nilai Batas Atas (K): ";
  //std::cin >> batas_atas;
  batas_atas = 100;
  std::cout << "Input Nilai Batas Bawah (K): ";
  //std::cin >> batas_bawah;
  batas_bawah = 150;
  std::cout << "Input Nilai Kondisi Awal (K): ";
  //std::cin >> kondisi_awal;
  kondisi_awal = 25;

  std::cout << std::endl;
  std::cout << "**Waktu Iterasi**";
  std::cout << std::endl;
  std::cout << "Input Waktu Total (s): ";
  //std::cin >> tot_waktu;
  tot_waktu = 10;
  std::cout << "Input Time-Step (s): ";
  //std::cin >> step_waktu;
  step_waktu = 0.02 ;
    if (step_waktu >= tot_waktu)
    {
        std::cout << "Time-Step Terlalu besar";
        return 0;
    }
  iterasi = tot_waktu / step_waktu;
  std::cout << "Jumlah Iterasi : " << iterasi << std::endl;
  std::cout << std::endl;

  //membuat matriks
  jum_baris = jum_baris_input + 2;
  jum_kolom = jum_kolom_input + 2;
  float matriks[jum_baris][jum_kolom];

  // proses input matriks
  for(int i = 0; i < jum_baris; i++)
  {
    for(int j = 0; j < jum_kolom; j++)
    {
        if (i == 0 && j == 0)
            {
                matriks[i][j] = 0;
            }
        else if (i == (jum_baris-1) && j == (jum_kolom-1))
            {
                matriks[i][j] = 0;
            }
        else if (i == (jum_baris-1) && j == 0)
            {
                matriks[i][j] = 0;
            }
        else if (i == 0 && j == (jum_kolom-1))
            {
                matriks[i][j] = 0;
            }
        else if (i == 0 && (j != 0 && j != (jum_kolom-1)))
            {
                matriks[i][j] = batas_atas;
            }
        else if ((i != 0 && i != (jum_baris-1)) && (j == 0))
            {
                matriks[i][j] = batas_kiri;
            }
        else if ((i != 0 && i != jum_baris-1) && j == (jum_kolom-1))
            {
                matriks[i][j] = batas_kanan;
            }
        else if (i == (jum_baris-1) && (j != 0 && j != (jum_kolom-1)))
            {
                matriks[i][j] = batas_bawah;
            }
        else
            {
                matriks[i][j] = kondisi_awal;
            }
    }
  }

  //Koefisien
  float ap0;
  float aw_NW, ae_NW, an_NW, as_NW, su_NW, sp_NW;
  float aw_NE, ae_NE, an_NE, as_NE, su_NE, sp_NE;
  float aw_SW, ae_SW, an_SW, as_SW, su_SW, sp_SW;
  float aw_SE, ae_SE, an_SE, as_SE, su_SE, sp_SE;
  float aw_N, ae_N, an_N, as_N, su_N, sp_N;
  float aw_E, ae_E, an_E, as_E, su_E, sp_E;
  float aw_S, ae_S, an_S, as_S, su_S, sp_S;
  float aw_W, ae_W, an_W, as_W, su_W, sp_W;
  float aw, ae, an, as, su, sp;

  ap0 = rho_C*(delta_x*delta_y)/step_waktu;

  aw = K*delta_y/delta_x;
  ae = K*delta_y/delta_x;
  an = K*delta_x/delta_y;
  as = K*delta_x/delta_y;
  su = 0;
  sp = 0;

  aw_NW = 0;
  ae_NW = K*delta_y/delta_x;
  an_NW = 0;
  as_NW = K*delta_x/delta_y;
  if (batas_atas == 0 && batas_kiri != 0)
  {
      su_NW = 2*K*delta_y*batas_kiri/delta_x;
      sp_NW = 2*K*delta_y/delta_x;
  }
  else if (batas_atas != 0 && batas_kiri == 0)
  {
      su_NW = 2*K*delta_x*batas_atas/delta_y;
      sp_NW = 2*K*delta_x/delta_y;
  }
  else if (batas_atas != 0 && batas_kiri != 0)
  {
      su_NW = (2*K*delta_y*batas_kiri/delta_x)+(2*K*delta_x*batas_atas/delta_y);
      sp_NW = (2*K*delta_y/delta_x)+(2*K*delta_x/delta_y);
  }

  aw_NE = K*delta_y/delta_x;
  ae_NE = 0;
  an_NE = 0;
  as_NE = K*delta_x/delta_y;
  if (batas_atas == 0 && batas_kanan != 0)
  {
      su_NE = 2*K*delta_y*batas_kanan/delta_x;
      sp_NE = 2*K*delta_y/delta_x;
  }
  else if (batas_atas != 0 && batas_kanan == 0)
  {
      su_NE = 2*K*delta_x*batas_atas/delta_y;
      sp_NE = 2*K*delta_x/delta_y;
  }
  else if (batas_atas != 0 && batas_kanan != 0)
  {
      su_NE = (2*K*delta_y*batas_kanan/delta_x)+(2*K*delta_x*batas_atas/delta_y);
      sp_NE = (2*K*delta_y/delta_x)+(2*K*delta_x/delta_y);
  }

  aw_SE = K*delta_y/delta_x;
  ae_SE = 0;
  an_SE = K*delta_x/delta_y;
  as_SE = 0;
  if (batas_bawah == 0 && batas_kanan != 0)
  {
      su_SE = 2*K*delta_y*batas_kanan/delta_x;
      sp_SE = 2*K*delta_y/delta_x;
  }
  else if (batas_bawah != 0 && batas_kanan == 0)
  {
      su_SE = 2*K*delta_x*batas_bawah/delta_y;
      sp_SE = 2*K*delta_x/delta_y;
  }
  else if (batas_bawah != 0 && batas_kanan != 0)
  {
      su_SE = (2*K*delta_y*batas_kanan/delta_x)+(2*K*delta_x*batas_bawah/delta_y);
      sp_SE = (2*K*delta_y/delta_x)+(2*K*delta_x/delta_y);
  }

  aw_SW = 0;
  ae_SW = K*delta_y/delta_x;
  an_SW = K*delta_x/delta_y;
  as_SW = 0;
  if (batas_bawah == 0 && batas_kiri != 0)
  {
      su_SW = 2*K*delta_y*batas_kiri/delta_x;
      sp_SW = 2*K*delta_y/delta_x;
  }
  else if (batas_bawah != 0 && batas_kiri == 0)
  {
      su_SW = 2*K*delta_x*batas_bawah/delta_y;
      sp_SW = 2*K*delta_x/delta_y;
  }
  else if (batas_bawah != 0 && batas_kiri != 0)
  {
      su_SW = (2*K*delta_y*batas_kiri/delta_x)+(2*K*delta_x*batas_bawah/delta_y);
      sp_SW = (2*K*delta_y/delta_x)+(2*K*delta_x/delta_y);
  }

  aw_N = K*delta_y/delta_x;
  ae_N = K*delta_y/delta_x;
  an_N = 0;
  as_N = K*delta_x/delta_y;
  if (batas_atas == 0)
  {
      su_N = 0;
      sp_N = 0;
  }
  else if (batas_atas != 0)
  {
      su_N = 2*K*delta_x*batas_atas/delta_y;
      sp_N = 2*K*delta_x/delta_y;
  }

  aw_E = K*delta_y/delta_x;
  ae_E = 0;
  an_E = K*delta_x/delta_y;
  as_E = K*delta_x/delta_y;
  if (batas_kanan == 0)
  {
      su_E = 0;
      sp_E = 0;
  }
  else if (batas_kanan != 0)
  {
      su_E = 2*K*delta_y*batas_kanan/delta_x;
      sp_E = 2*K*delta_y/delta_x;
  }

  aw_S = K*delta_y/delta_x;
  ae_S = K*delta_y/delta_x;
  an_S = K*delta_x/delta_y;
  as_S = 0;
  if (batas_bawah == 0)
  {
      su_S = 0;
      sp_S = 0;
  }
  else if (batas_bawah != 0)
  {
      su_S = 2*K*delta_x*batas_bawah/delta_y;
      sp_S = 2*K*delta_x/delta_y;
  }

  aw_W = 0;
  ae_W = K*delta_y/delta_x;
  an_W = K*delta_x/delta_y;
  as_W = K*delta_x/delta_y;
  if (batas_kiri == 0)
  {
      su_W = 0;
      sp_W = 0;
  }
  else if (batas_kiri != 0)
  {
      su_W = 2*K*delta_y*batas_kiri/delta_x;
      sp_W = 2*K*delta_y/delta_x;
  }

  //Iterasi ke 0
  std::cout << "Iterasi ke : 0" << std::endl;
  for (int i = 0; i < jum_baris; ++i)
    {
        for (int j = 0; j < jum_kolom; ++j)
        {
            std::cout << matriks[i][j] << " ";
        }
        std::cout << std::endl;
    }

  std::cout << std::endl;

  //Duplikasi Matriks
  float** matriks_temp = new float*[jum_baris];
  for (int i = 0; i < jum_baris; ++i)
    {
        matriks_temp[i] = new float[jum_kolom];
    }

  for (int i = 0; i < jum_baris; ++i)
    {
        for (int j = 0; j < jum_kolom; ++j)
            {
                matriks_temp[i][j] = matriks[i][j];
            }
    }

  //Iterasi
  for (int k = 0; k < iterasi; ++k)
    {
        for (int i = 1; i < jum_baris; ++i)
          {
                for (int j = 1; j < jum_kolom; ++j)
                {
                    if (i == 1 && j == 1)
                    {
                        matriks[i][j] = ((aw_NW*matriks_temp[i][j-1])+(ae_NW*matriks_temp[i][j+1])+(an_NW*matriks_temp[i-1][j])+(as_NW*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_NW+ae_NW+an_NW+as_NW+sp_NW)))+su_NW)/ap0;
                    }
                    else if (i == 1 && (j == jum_kolom_input))
                    {
                        matriks[i][j] = ((aw_NE*matriks_temp[i][j-1])+(ae_NE*matriks_temp[i][j+1])+(an_NE*matriks_temp[i-1][j])+(as_NE*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_NE+ae_NE+an_NE+as_NE+sp_NE)))+su_NE)/ap0;
                    }
                    else if (i == jum_baris_input && j == jum_kolom_input)
                    {
                        matriks[i][j] = ((aw_SE*matriks_temp[i][j-1])+(ae_SE*matriks_temp[i][j+1])+(an_SE*matriks_temp[i-1][j])+(as_SE*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_SE+ae_SE+an_SE+as_SE+sp_SE)))+su_SE)/ap0;
                    }
                    else if (i == jum_baris_input && j == 1)
                    {
                        matriks[i][j] = ((aw_SW*matriks_temp[i][j-1])+(ae_SW*matriks_temp[i][j+1])+(an_SW*matriks_temp[i-1][j])+(as_SW*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_SW+ae_SW+an_SW+as_SW+sp_SW)))+su_SW)/ap0;
                    }
                    else if (i == 1 && (j > 1 && j < jum_kolom_input))
                    {
                        matriks[i][j] = ((aw_N*matriks_temp[i][j-1])+(ae_N*matriks_temp[i][j+1])+(an_N*matriks_temp[i-1][j])+(as_N*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_N+ae_N+an_N+as_N+sp_N)))+su_N)/ap0;
                    }
                    else if ((i > 1 && i < jum_baris_input) && j == jum_kolom_input)
                    {
                        matriks[i][j] = ((aw_E*matriks_temp[i][j-1])+(ae_E*matriks_temp[i][j+1])+(an_E*matriks_temp[i-1][j])+(as_E*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_E+ae_E+an_E+as_E+sp_E)))+su_E)/ap0;
                    }
                    else if (i == jum_baris_input && (j > 1 && j < jum_kolom_input))
                    {
                        matriks[i][j] = ((aw_S*matriks_temp[i][j-1])+(ae_S*matriks_temp[i][j+1])+(an_S*matriks_temp[i-1][j])+(as_S*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_S+ae_S+an_S+as_S+sp_S)))+su_S)/ap0;
                    }
                    else if ((i > 1 && i < jum_baris_input) && j == 1)
                    {
                        matriks[i][j] = ((aw_W*matriks_temp[i][j-1])+(ae_W*matriks_temp[i][j+1])+(an_W*matriks_temp[i-1][j])+(as_W*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw_W+ae_W+an_W+as_W+sp_W)))+su_W)/ap0;
                    }
                    else if ((i > 1 && i < jum_baris_input) && (j > 1 && j < jum_kolom_input))
                    {
                        matriks[i][j] = ((aw*matriks_temp[i][j-1])+(ae*matriks_temp[i][j+1])+(an*matriks_temp[i-1][j])+(as*matriks_temp[i+1][j])+(matriks_temp[i][j]*(ap0-(aw+ae+an+as+sp)))+su)/ap0;
                    }
                }
          }

        std::cout << "Iterasi ke : " << k+1 << std::endl;
        if (k == iterasi - 1)
        {
            for (int i = 0; i < jum_baris; ++i)
            {
            for (int j = 0; j < jum_kolom; ++j)
                {
                    std::cout << matriks[i][j] << " ";
                }
            std::cout << std::endl;
            }
        }

        //std::cout << std::endl;

        for (int i = 0; i < jum_baris; ++i)
        {
            for (int j = 0; j < jum_kolom; ++j)
                {
                    matriks_temp[i][j] = matriks[i][j];
                }
        }
    }

  //Membuat matriks koordinat
  float matriks_baris [jum_baris_input][jum_kolom_input];
  float matriks_kolom [jum_baris_input][jum_kolom_input];

  //Membuat koordinat posisi baris
  std::cout << "Koordinat X" << std::endl;
  for (int i = 0; i < jum_baris_input; ++i)
    {
        for (int j = 0; j < jum_kolom_input; ++j)
        {
            if (j == 0)
            {
                matriks_baris[i][j] = 0.5 * delta_x;
            }
            else
            {
                matriks_baris[i][j] = (j * delta_x) + (0.5 * delta_x);
            }
            std::cout << matriks_baris[i][j] << " ";
        }
        std::cout << std::endl;
    }

  std::cout << std::endl;

  //Membuat koordinat posisi kolom
  std::cout << "Koordinat Y" << std::endl;
  for (int i = 0; i < jum_baris_input; ++i)
    {
        for (int j = 0; j < jum_kolom_input; ++j)
        {
            matriks_kolom[i][j] = (jum_baris_input*delta_x) - (i * delta_x + delta_x/2);
            std::cout << matriks_kolom[i][j] << " ";
        }
        std::cout << std::endl;
    }

  return 0;
}
