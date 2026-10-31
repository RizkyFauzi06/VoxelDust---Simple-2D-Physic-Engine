#include <iostream>
#include <array>
#include <raylib.h>
    // size window
    const int screenWidth = 1080;
    const int screenHeight = 720;

    // Data Scope
    const int KolomSize = 108; // Size Array
    const int BarisSize = 72; // Size Array
    int Nilai[BarisSize][KolomSize] = {0};
    // Prioritas:    1(Bawah) | 2(Bwh-Kiri) | 3(Bwh-Kanan) | 4(Kiri) | 5(Kanan)
    int dx[5]  = {     0,          -1,             1,          -1,        1    };
    int dy[5] = {     1,           1,             1,           0,        0   };


    int elemenAktif = 1;
    void InputEntitas() {
    if (IsKeyPressed(KEY_ONE)) elemenAktif = 1;
    if (IsKeyPressed(KEY_TWO)) elemenAktif = 2;
    if (IsKeyPressed(KEY_THREE)) elemenAktif = 3;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int mouseX = mousePos.x / 10;
        int mouseY = mousePos.y / 10;
        if (mouseX >= 0 && mouseX < KolomSize && mouseY >= 0 && mouseY < BarisSize) {
            Nilai[mouseY][mouseX] = elemenAktif;
             }
        }
    }


    void UpdateFisika(){
        for(int y = BarisSize - 2;  y > 0; y--){
            for(int x = 0; x < KolomSize; x++){
                int EntitasDilayar = Nilai[y][x];

                if(EntitasDilayar == 1){
                    for(int i = 0; i < 3; i++){
                        int ArahAcak = (GetRandomValue(0, 1) == 0) ? 1 : -1;

                        int targetY = y + dy[i];
                        int targetX = x + (dx[i] * ArahAcak);

                        if (targetX >= 0 && targetX < KolomSize && targetY < BarisSize){
                            
                            if (Nilai[targetY][targetX] == 0) {
                            Nilai[y][x] = 0;             // Hapus posisi lama
                            Nilai[targetY][targetX] = 1; // Taruh di posisi baru
                            break;
                                 }
                            }

                        }                     

                    }
        

                if(EntitasDilayar == 2){
                    for(int i = 0; i < 5; i++){
                        int ArahAcak = (GetRandomValue(0, 1) == 0) ? 1 : -1;
                        int targetY = y + dy[i];
                        int targetX = x + (dx[i] * ArahAcak);

                        if (targetX >= 0 && targetX < KolomSize && targetY < BarisSize){
                            
                            if (Nilai[targetY][targetX] == 0) {
                            Nilai[y][x] = 0;             
                            Nilai[targetY][targetX] = 2;
                            break;
                                 }
                            }
                        }

                    }

                if(EntitasDilayar == 3){
                    Nilai[y][x] = 3;
                }
            }   
        }
    }

        




    void Draw(){
        for(int y = 0; y < BarisSize; y++){
            for(int x = 0; x < KolomSize; x++){
                int EntitasDilayar = Nilai[y][x];
                if(EntitasDilayar == 1){
                    DrawRectangle( x * 10, y * 10, 10, 10, YELLOW);
                }
                
                if(EntitasDilayar == 2){
                    DrawRectangle( x * 10, y * 10, 10, 10, BLUE);
                }

                if(EntitasDilayar == 3){
                    DrawRectangle( x * 10, y * 10, 10, 10, GRAY);
                }

            }
        }
    }

    enum GameState{
    MENU,
    PLAYING,
    GAMEOVER
        };
        
int main(){
    InitWindow(screenWidth, screenHeight, "Cecullar Automata simulation");
    GameState state = MENU;
    bool GameOver = false;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            if(state == MENU){
                DrawText("2D VOXEL SIMULATION",305,200,45,GOLD);
            DrawRectangle(
                380,320,
                350,80,
                BLUE
            );
            DrawText(
                "PLAY",
                510,345,
                30,
                WHITE
            );

             Vector2 mouse = GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {

                if(CheckCollisionPointRec(mouse,{380,320,350,80})){
                    state = PLAYING;
                    }
                }
            }

            else if(state == PLAYING)
            {
                DrawText(
                "Pilih Material (Klik Nomor di keyboard) : ",
                50,40,
                30,
                WHITE
                     );
                DrawText(
                "1. Pasir",
                50,80,
                30,
                YELLOW
                     );
                DrawText(
                "2. Air",
                200,80,
                30,
                BLUE
                     );
                DrawText(
                "3. Batu",
                350,80,
                30,
                GRAY
                     );
                DrawText(
                "R (Reset / Done)",
                500,80,
                30,
                RED
                     );     
                     
                     
                if(!GameOver){
                    if(IsKeyPressed(KEY_R)){
                        GameOver = true;
                        }
                    InputEntitas();
                    UpdateFisika();
                    Draw();
                }else{
                    state = GAMEOVER;
                }
                
            }

            else if(state == GAMEOVER){
                 DrawText("GAME OVER", 380,240, 45,RED);
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //------------------
    return 0;
}