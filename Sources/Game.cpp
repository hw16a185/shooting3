#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)hw16a185松本聖司
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)hw16a185松本聖司
// TODO: 砲台を青い壁に沿って上下に動かす。(C) 実装：HW15A215 山領萌美
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D) 実装：HW15A215 山領萌美
// TODO: スコアのサイズを大きくする。(E) Hw16A100 須賀 康則
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F) HW16A100 須賀 康則
// TODO: PlayBGM()関数を使って、BGMを再生する。(G) HW16A100 須賀 康則
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)hw16a185松本聖司


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
int     cannon_y;       //!< キャノンの上下繰り返し用


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);
    targetRect = Rect(280, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;

    cannon_y = 1;
    
    // BGMを再生する。(G) HW16A100 須賀 康則
    PlayBGM("bgm_maoudamashii_8bit07.mp3");
    cannon_y = 1;
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{

    // 弾のスピード変更および画面端で弾を戻す 実装：HW15A215 山領萌美
    // 弾の発射
    if (bulletPos.x <= -999  && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 100 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion03.mp3");//se

        }
        if(bulletPos.x > 320){
            bulletPos.x = -999;
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    cloudPos.x += 15;
    if (cloudPos.x >= 320) {
        cloudPos.x = -500;
    }
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    // 青い壁に沿って上下に動か ない 実装：HW15A215 山領萌美
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    if(cannonPos.y <= -65 && cannonPos.y >= -150){
        cannonPos.y += 0.5 * cannon_y;
    }else{
        cannon_y *= -1;
    }
    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画 HW16A100 須賀 康則
    SetFont("nicoca_v1.ttf", 80.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 179), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 180), Color::white);
}

