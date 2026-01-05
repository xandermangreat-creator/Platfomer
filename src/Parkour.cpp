#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int main()
{
    srand((unsigned int)time(0));

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Parkour!", Style::Fullscreen);

    Texture texturePlayer;
    texturePlayer.loadFromFile("assets/Player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(20, 800);

    Texture textureEnemy;
    textureEnemy.loadFromFile("assets/Enemy.png");
    Sprite spriteEnemy;
    spriteEnemy.setTexture(textureEnemy);
    spriteEnemy.setPosition((rand() % 1920) + 1, 800);

    Texture textureBlock;
    textureBlock.loadFromFile("assets/Block.png");
    Sprite spriteBlock;
    spriteBlock.setTexture(textureBlock);
    spriteBlock.setPosition((rand() % 1920) + 1, (rand() % 1080) + 1);

    Texture textureSpike;
    textureSpike.loadFromFile("assets/Spike.png");
    Sprite spriteSpike;
    spriteSpike.setTexture(textureSpike);
    spriteSpike.setPosition((rand() % 1920) + 1, 800);

    Texture textureGrass;
    textureGrass.loadFromFile("assets/Grass.png");
    Sprite spriteGrass;
    spriteGrass.setTexture(textureGrass);
    spriteGrass.setPosition((rand() % 1920) + 1, 800);

    Texture textureSky;
    textureSky.loadFromFile("assets/Sky.png");
    Sprite spriteSky;
    spriteSky.setTexture(textureSky);
    spriteSky.setPosition(0, 0);

    Text messageText;
    messageText.setCharacterSize(100);
    messageText.setFillColor(Color::Black);
    Font font;
    font.loadFromFile("Arial.ttf");
    messageText.setFont(font);
    messageText.setString("Press Space to Start!");
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    SoundBuffer jumpBuffer;
    jumpBuffer.loadFromFile("assets/Jump.mp4.m4a");
    Sound jumpSound;
    jumpSound.setBuffer(jumpBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("assets/Death.mp4.m4a");
    Sound deathSound;
    deathSound.setBuffer(deathBuffer);

    SoundBuffer landingBuffer;
    landingBuffer.loadFromFile("assets/Landing.mp4.m4a");
    Sound landingSound;
    landingSound.setBuffer(landingBuffer);

    SoundBuffer walkBuffer;
    walkBuffer.loadFromFile("assets/Walk.mp4.m4a");
    Sound walkSound;
    walkSound.setBuffer(walkBuffer);

    SoundBuffer GrassBuffer;
    GrassBuffer.loadFromFile("assets/Grass.mp4.m4a");
    Sound grassSound;
    grassSound.setBuffer(GrassBuffer);

    SoundBuffer killBuffer;
    killBuffer.loadFromFile("assets/Kill.mp4.m4a");
    Sound killSound;
    killSound.setBuffer(killBuffer);

    SoundBuffer scoreBuffer;
    scoreBuffer.loadFromFile("assets/Score.mp4.m4a");
    Sound scoreSound;
    scoreSound.setBuffer(scoreBuffer);

    Text scoreText;
    scoreText.setCharacterSize(75);
    scoreText.setFillColor(Color::Black);
    scoreText.setFont(font);
    scoreText.setPosition(20, 20);
    int currentScore = 0;
    int highScore = 0;

    float playerXCoord = 50.0f;
    float playerYCoord = 800.0f;
    float playerXVelocity = 600.0f;
    float playerYVelocity = 0.0f;
    float gravity = 0.5f;
    float jump = -10.0f;
    float enemyVelocity = 400.0f;
    float scrollSpeed = 500.0f;

    Clock clock;
    Time updateIntervalTime = seconds(10.0f);
    Time elapsedTime = 0;

    bool running = false;

    while (window.isOpen())
    {
        Time dt = clock.restart();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            running = false;
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            running = true;
            playerYVelocity = 200;
            if (playerYCoord < 800)
            {
                playerYCoord += gravity;
                if (playerYCoord == 800)
                {
                    landingSound.play();
                }
            }
            else
            {
                playerYCoord = 800;
                playerYVelocity = jump;
                jumpSound.play();
            }
            playerYCoord += playerYVelocity;
        }

        while (running)
        {
            spritePlayer.setPosition(spritePlayer.getPosition().x + (playerXVelocity * dt.asSeconds), spritePlayer.getPosition().y);
            walkSound.play();
            spriteEnemy.setPosition(spriteEnemy.getPosition().x + (enemyVelocity * dt.asSeconds()), 800);
            spriteBlock.setPosition(spriteBlock.getPosition().x + (scrollSpeed * dt.asSeconds()), spriteBlock.getPosition().y);
            spriteGrass.setPosition(spriteGrass.getPosition().x + (scrollSpeed * dt.asSeconds()), 800);
            spriteSpike.setPosition(spriteSpike.getPosition().x + (scrollSpeed * dt.asSeconds()), 800);

            if (spritePlayer.getGlobalBounds().intersects(spriteEnemy.getGlobalBounds()))
            {
                running = false;
                killSound.play();
                if (currentScore > highScore && running == false)
                {
                    highScore = currentScore;
                }
                currentScore = 0;
                spritePlayer.setPosition(20, 800);
                spriteEnemy.setPosition((rand() % 1920) + 1, 800);
                spriteBlock.setPosition((rand() % 1920) + 1, (rand() % 1080) + 1);
                spriteSpike.setPosition((rand() % 1920) + 1, 800);
                spriteGrass.setPosition((rand() % 1920) + 1, 800);
            }

            elapsedTime += dt;
            if (elapsedTime == updateIntervalTime)
            {
                currentScore += 100;
                scoreSound.play();
                elapsedTime = 0;
            }

            std::stringstream ss;
            ss << "Score: " << currentScore << "  High Score: " << highScore << "   Time: " << elapsedTime.asSeconds();
            scoreText.setString(ss.str());

            if (spritePlayer.getGlobalBounds().intersects(spriteSpike.getGlobalBounds()))
            {
                running = false;
                deathSound.play();
                if (currentScore > highScore && running == false)
                {
                    highScore = currentScore;
                    currentScore = 0;
                    spritePlayer.setPosition(20, 800);
                    spriteEnemy.setPosition((rand() % 1920) + 1, 800);
                    spriteBlock.setPosition((rand() % 1920) + 1, (rand() % 1080) + 1);
                    spriteSpike.setPosition((rand() % 1920) + 1, 800);
                    spriteGrass.setPosition((rand() % 1920) + 1, 800);
                }
            }

            if (spritePlayer.getGlobalBounds().intersects(spriteGrass.getGlobalBounds()))
            {
                grassSound.play();
            }
        }

        window.clear();

        window.draw(spriteSky);
        window.draw(spriteEnemy);
        window.draw(spritePlayer);
        window.draw(spriteGrass);
        window.draw(spriteBlock);
        window.draw(spriteSpike);

        window.display();
    }

    return 0;
}