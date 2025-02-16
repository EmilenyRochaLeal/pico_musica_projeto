# 🎵 Pico Música Projeto 🇧🇷

Projeto desenvolvido para a etapa final do programa **EmbarcaTech**.  
Este projeto utiliza o kit de desenvolvimento **BitDogLab** com a placa **Raspberry Pi Pico** para:

✅ **Exibir a bandeira do Brasil** em um display OLED 📺  
✅ **Tocar o Hino Nacional Brasileiro** através de um buzzer 🎶  
✅ **Sincronizar LEDs** piscando conforme a melodia ✨  

---

## 📸 Demonstração  
*🎥 [Assista ao vídeo no Google Drive](https://drive.google.com/file/d/1mZjT8pG70cVM45tFM_qZFiQH78tezaNR/view?usp=drive_link)
*  

---
## 🚀 Como Funciona?

### 🖥️ Imagem no Display OLED  
- O **display exibe a bandeira do Brasil**   
- A imagem aparece em bitmap_128x64 
- imagem formatada no site [Image2cpp](https://javl.github.io/image2cpp/)
- o código bitmap da imagem está no arquivo **`display_oled.c`**.

### 🎶 Tocando Música  
- As notas musicais, a melodia e a duração estão definidas no arquivo **`notes.h`**.  
- O buzzer é controlado pela **`hardware/pwm.h`** do **Raspberry Pi Pico**.  
- Inicializa a saída PWM do buzzer no pino 21, os LEDs como saída digital, garantir que todos os LEDs começam desligados no arquivo **`play_audio.c`**

### 💡 LEDs Sincronizados  
- **LEDs piscam conforme a frequência** das notas musicais.   


## 📂 Estrutura do Projeto

📦 **pico_musica_projeto**  
 ┣ 📂 **inc** *(Arquivos de cabeçalho - .h)*  
 ┃ ┣ 📜 **notes.h** – Definição das notas musicais  
 ┃ ┣ 📜 **play_audio.h** – Declarações para controle do buzzer e LEDs  
 ┃ ┣ 📜 **ssd1306.h** – Biblioteca para comunicação com OLED  
 ┃ ┣ 📜 **ssd1306_i2c.h** – Comunicação via I2C com OLED  
 ┣ 📂 **src** *(Código-fonte principal - .c)*  
 ┃ ┣ 📜 **display_oled.c** – Exibição da bandeira no OLED, além de tocar áudio e sincronizar LEDs  
 ┃ ┣ 📜 **play_audio.c** – Controle do buzzer e LEDs sincronizados  
 ┃ ┣ 📜 **ssd1306_i2c.c** – Implementação da comunicação I2C com OLED  
 ┣ 📜 **CMakeLists.txt** – Configuração do projeto para compilação  
 ┣ 📜 **README.md** – Este arquivo de documentação  



## 🏆 Créditos

- 👤 **Desenvolvedora:** [Emileny Leal]
- 📅 **Data:** Fevereiro de 2025
- 🏫 **Projeto Final - EmbarcaTech**
