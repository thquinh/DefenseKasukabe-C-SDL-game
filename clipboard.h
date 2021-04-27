if (((i == tempR - 1 && j == tempC) || (i == tempR + 1 && j == tempC) ||
    (i == tempR && j == tempC - 1) || ((i == tempR && j == tempC + 1)))) {
    swap(Img_Board[i][j].mark, Img_Board[tempR][tempC].mark);
    Img_Board[i][j].moveTile(Img_Board[tempR][tempC], true);
    if (!Find_Match(hidden_point)) {
        swap(Img_Board[i][j].mark, Img_Board[tempR][tempC].mark);
        Img_Board[i][j].render_match(Img_Board[tempR][tempC], true);
        Img_Board[i][j].Update_status();
        Img_Board[tempR][tempC].Update_status();
        Img_Board[i][j].render();
        Img_Board[tempR][tempC].render();
        Mix_PlayChannel(1, reverse_sound, 0);
    }
}
else
{
    Img_Board[i][j].render_match(Img_Board[tempR][tempC], false);
    Img_Board[i][j].Update_status();
    Img_Board[tempR][tempC].Update_status();
    Img_Board[i][j].render();
    Img_Board[tempR][tempC].render();
}


if (Rev) {
    status = Tile_Status::Selected_Valid;
    otherTile.status = Tile_Status::Selected_Valid;
    render();
    otherTile.render();
    Update_status();
    otherTile.Update_status();
    render();
    otherTile.render();
}
else {
    status = Tile_Status::Selected_Invalid;
    otherTile.status = Tile_Status::Selected_Invalid;
    render();
    otherTile.render();
}
void Tile::dropTile(Tile otherTile, SDL_Renderer * Game_render)
{
    SDL_Rect otherRect = otherTile.Tile_rect;
    for (; otherRect.y < Tile_rect.y;) {
        otherRect.y += 20;
        cout << otherRect.y << endl;
        if (otherRect.y > Tile_rect.y) otherRect.y = Tile_rect.y;
        SDL_RenderCopy(Drenderer, otherTile.texture, NULL, &otherRect);
        SDL_RenderPresent(Drenderer);
        otherTile.render_empty();
    }
}