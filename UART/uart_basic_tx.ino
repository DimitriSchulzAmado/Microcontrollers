int main(){
    UBRR0 = 103; // BAUD RATE DE 9600 bps
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Definição da quantidade de dados (8 bits)
    UCSR0B = (1 << TXEN0); // Habilita transmissão 
    
    // DEFINIÇÃO DO DADO A SER TRANSMITIDO
    unsigned char dado[] = 'INATEL';
    int i = 0; // indice do vetor 'dado'

    while(true){
        // CHECAR SE HÁ DADOS PARA TRANSMITIR
        while (dado[i] != 0){
            // CHECAR SE O BUFFER ESTÁ VAZIO
            if(!(UCSR0A & (1 << UDRE0))){
                UDR0 = dado[i]; // Carrega o dado no buffer
                i++;
            }
        }
    }
}