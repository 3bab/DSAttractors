#include "DSAttractors.h"

using namespace sf;
using namespace std;

DSAttractors::DSAttractors() {
    setupText();

    view.setCenter(Vector2f(0.0f, 0.0f));
    view.setSize(Vector2f(static_cast<float>(screenWidth / 10), static_cast<float>(screenHeight / 10)));

    attractorConfig = {
            {10.0f,  30.0f,  8 / 3},
            {1.24f,  1.1f,   4.4f, 3.21f},
            {0.95f,  0.7f,   0.6f, 3.5f, 0.25f, 0.1f},
            {0.3f,   1.0f},
            {5.0f,   -10.0f, -0.38f},
            {1.4f},
            {0.001f, 0.2f,   1.1f},
            {0.4f,   0.175f},
            {1.5f},
            {0.2f}
    };

    colours = {
            Color(115, 62, 101, 42), // 42
            Color(255, 126, 210, 127),
            Color(109, 193, 202, 179),
            Color(135, 216, 10, 203),
            Color(125, 26, 133, 99),
            Color(8, 161, 163, 57),
            Color(134, 184, 38, 183),
            Color(132, 159, 149, 188),
            Color(100, 195, 167, 160),
            Color(190, 242, 126, 252),
    };

    trailColoursParams = {
            {61.3f,     62.1f,     33.9f},
            {-65.5125f, -27.8521f, -97.0907f},
            {-47.3382f, -49.5409f, -33.8347f},
            {-12.9346f, -76.7609f, 70.7356f},
            {-12.0673f, 51.6949f,  97.4566f},
            {93.4094f,  -16.196f,  40.8949f},
            {-37.5288f, -31.3912f, -48.0061f},
            {-5.6245f,  -49.0192f, 19.271f},
            {98.011f,   -81.8857f, -80.084f},
            {44.3435f,  -93.5679f, -52.0752f},
    };

    cout << "\n\n\n";
    for (unsigned c = 0; c < colours.size(); c++) {
        cout << static_cast<int>(colours[c].r) << " " <<
             static_cast<int>(colours[c].g) << " " <<
             static_cast<int>(colours[c].b) << " " <<
             static_cast<int>(colours[c].a) << endl;
        cout << trailColoursParams[c][0] << " " << trailColoursParams[c][1] << " "
             << trailColoursParams[c][2] << endl;
    }

    circle.resize(numPoints);
    point.resize(numPoints);
    trail.resize(numPoints);

    // Create trial trackers
    for (unsigned i = 0; i < numPoints; i++) {
        j.push_back(0);
    }

    createBalls();

    // Create lineStrip object with two vertices. The first line should start with a first point.
    line.setPrimitiveType(LinesStrip);
    line.append(Vector2f(point[0].x, point[0].y));
    line.append(Vector2f(point[0].x, point[0].y));

    initiateCamera();
}

void DSAttractors::initiateCamera() {// Set Camera
    switch (attractorIndex) {
        case 0: {
            camPosition = {0, 0, -50};
            camAngle = {0, 0, 0};
            break;
        }
        case 1: {
            camPosition = {1.07676f, 0.3f, -0.447995f};
            camAngle = {0.1f, 4.84f, 0.0f};
            break;
        }
        case 2: {
            camPosition = {2.25, 0, 0.75};
            camAngle = {0, -PI / 2, 0};
            break;
        }
        case 3: {
            camPosition = {-7.5, 5, -15};
            camAngle = {0, PI / 6, 0};
            break;
        }
        case 4: {
            camPosition = {51.310f, -4.8f, 25.151f};
            camAngle = {-0.16f, -2.1f, 0.0f};
            break;
        }
        case 5: {
            camPosition = {-23.357f, -16.4f, -20.731f};
            camAngle = {-0.5f, -5.48f, 0.0f};
            break;
        }
        case 6: {
            camPosition = {1.0216f, -5.7f, 6.1861f};
            camAngle = {-0.16f, 3.34f, 0.0f};
            break;
        }
        case 7: {
            camPosition = {0, 0, -0.5};
            camAngle = {0, 0, -0.134f};
            break;
        }
        case 8: {
            camPosition = {-0.14397f, -8.4f, -1.3497f};
            camAngle = {-1.66f, -2.94f, 0};
            break;
        }
        case 9: {
            camPosition = {7.1565f, 4.2f, 2.6844f};
            camAngle = {0.48f, -1.92f, 0};
            break;
        }
    }
}

void DSAttractors::createBalls() {
    for (unsigned i = 0; i < numPoints; i++) {
        // Create balls
        circle[i].setRadius(0.5f);
        circle[i].setOrigin(circle[i].getRadius(), circle[i].getRadius());
        circle[i].setFillColor(colours[attractorIndex]);

        // Set initial positions
        point[i] = {getRandomNumber(1.0f, 1.0f), getRandomNumber(1.0f, 1.0f), getRandomNumber(1.0f, 1.0f)};

        // Create trails
        trail[i].resize(trailLength);
        for (auto &pos : trail[i]) {
            pos = point[i];
        }
    }
}

void DSAttractors::setupText() {
    font.loadFromFile("/Users/gintas.palionis/CLionProjects/DSAttractors/arial.ttf");
    text.setFont(font);
    text.setFillColor(Color(100, 0, 0, 255));
    text.setString(attractorNames[attractorIndex]);
    text.setScale(0.1f, 0.1f);
    text.setPosition(Vector2f(-85, -45));
    text.setStyle(0);
}

void DSAttractors::input(RenderWindow &window) {
    while (window.pollEvent(event)) {
        // Window
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            endSubProgram = true;
        if (Keyboard::isKeyPressed(Keyboard::F)) {
            isFullscreen = !isFullscreen;
            window.create(VideoMode(static_cast<int>(screenWidth), static_cast<int>(screenHeight)),
                          "Coding Projects", (isFullscreen ? Style::Fullscreen : Style::Default), ContextSettings());
            window.setPosition(Vector2i(0, 0));
            window.setVerticalSyncEnabled(true);
            window.setFramerateLimit(60);
        }
        if ((Keyboard::isKeyPressed(Keyboard::H) || Keyboard::isKeyPressed(Keyboard::G)) && inputTimer >= 0.1) {
            inputTimer = 0;

            if (Keyboard::isKeyPressed(Keyboard::H)) {
                attractorIndex++;
                if (attractorIndex == attractorConfig.size())
                    attractorIndex--;
            } else {
                attractorIndex--;
                if (attractorIndex == -1)
                    attractorIndex++;
            }

            switch (attractorIndex) {
                case 0: {
                    camPosition = {0, 0, -50};
                    camAngle = {0, 0, 0};
                    break;
                }
                case 1: {
                    camPosition = {1.07676f, 0.3f, -0.447995f};
                    camAngle = {0.1f, 4.84f, 0.0f};
                    break;
                }
                case 2: {
                    camPosition = {2.25, 0, 0.75};
                    camAngle = {0, -PI / 2, 0};
                    break;
                }
                case 3: {
                    camPosition = {-7.5, 5, -15};
                    camAngle = {0, PI / 6, 0};
                    break;
                }
                case 4: {
                    camPosition = {51.310f, -4.8f, 25.151f};
                    camAngle = {-0.16f, -2.1f, 0};
                    break;
                }
                case 5: {
                    camPosition = {-23.357f, -16.4f, -20.731f};
                    camAngle = {-0.5f, -5.48f, 0.0f};
                    break;
                }
                case 6: {
                    camPosition = {1.0216f, -5.7f, 6.1861f};
                    camAngle = {-0.16f, 3.34f, 0.0f};
                    break;
                }
                case 7: {
                    camPosition = {0, 0, -0.5};
                    camAngle = {0, 0, 0};
                    break;
                }
                case 8: {
                    camPosition = {-0.1439f, -8.4f, -1.3497f};
                    camAngle = {-1.66f, -2.94f, 0};
                    break;
                }
                case 9: {
                    camPosition = {7.1565f, 4.2f, 2.6844f};
                    camAngle = {0.48f, -1.92f, 0};
                    break;
                }
            }
            const float max = 0.001f;
            const float min = -max;
            for (unsigned i = 0; i < numPoints; i++) {
                circle[i].setFillColor(colours[attractorIndex]);

                point[i] = {getRandomNumber(min, max), getRandomNumber(min, max), getRandomNumber(min, max)};
            }
            for (unsigned i = 0; i < numPoints; i++) {
                for (auto &pos : trail[i])
                    pos = point[i];
            }

            text.setString(attractorNames[attractorIndex]);
        }
    }
}

void DSAttractors::update() {
    /// Calculate timeStep
    timeStep = clock.getElapsedTime().asSeconds();
    inputTimer += timeStep;
    clock.restart();

    timeStep *= speed; // Slow down or speed up time.

    // Update position according to chosen equation attractorIndex
    vector<float> &attractorParams = attractorConfig.at(attractorIndex);
    switch (attractorIndex) {
        case 0: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>(attractorParams[0] * (point[i].y - point[i].x) * timeStep);
                point[i].y += static_cast<float>((point[i].x * (attractorParams[1] - point[i].z) - point[i].y) *
                                                 timeStep);
                point[i].z += static_cast<float>((point[i].x * point[i].y - attractorParams[2] * point[i].z) *
                                                 timeStep);
            }
            break;
        }
        case 1: {
            for (unsigned i = 0; i < numPoints; i++) {
                float h1 = 0.5f * (abs(point[i].x + 1) - abs(point[i].x - 1));
                float h2 = 0.5f * (abs(point[i].y + 1) - abs(point[i].y - 1));
                float h3 = 0.5f * (abs(point[i].z + 1) - abs(point[i].z - 1));

                point[i].x += static_cast<float>(
                        (-point[i].x + attractorParams[0] * h1 - attractorParams[3] * h2 - attractorParams[3] * h3) *
                        timeStep);
                point[i].y += static_cast<float>(
                        (-point[i].y - attractorParams[3] * h1 + attractorParams[1] * h2 - attractorParams[2] * h3) *
                        timeStep);
                point[i].z += static_cast<float>(
                        (-point[i].z - attractorParams[3] * h1 + attractorParams[2] * h2 + h3) * timeStep);
            }
            break;
        }
        case 2: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>(
                        ((point[i].z - attractorParams[1]) * point[i].x - attractorParams[3] * point[i].y) * timeStep);
                point[i].y += static_cast<float>(
                        (attractorParams[3] * point[i].x + (point[i].z - attractorParams[1]) * point[i].y) * timeStep);
                point[i].z += static_cast<float>(
                        (attractorParams[2] + attractorParams[0] * point[i].z -
                         (point[i].z * point[i].z * point[i].z) / 3 -
                         (point[i].x * point[i].x + point[i].y * point[i].y) * (1 + attractorParams[4] * point[i].z) +
                         attractorParams[5] * point[i].z * point[i].x * point[i].x * point[i].x) * timeStep);
            }
            break;
        }
        case 3: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>((point[i].x * (4 - point[i].y) + attractorParams[0] * point[i].z) *
                                                 timeStep);
                point[i].y += static_cast<float>((-point[i].y * (1 - point[i].x * point[i].x)) * timeStep);
                point[i].z += static_cast<float>(
                        (-point[i].x * (1.5 - point[i].z * attractorParams[1]) - 0.05 * point[i].z) *
                        timeStep);
            }
            break;
        }
        case 4: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>((attractorParams[0] * point[i].x - point[i].y * point[i].z) *
                                                 timeStep * 0.25f);
                point[i].y += static_cast<float>((attractorParams[1] * point[i].y + point[i].x * point[i].z) *
                                                 timeStep * 0.25f);
                point[i].z += static_cast<float>((attractorParams[2] * point[i].z + point[i].x * point[i].y / 3) *
                                                 timeStep * 0.25f);
            }
            break;
        }
        case 5: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>(
                        (-attractorParams[0] * point[i].x - 4 * point[i].y - 4 * point[i].z - point[i].y * point[i].y) *
                        timeStep);
                point[i].y += static_cast<float>(
                        (-attractorParams[0] * point[i].y - 4 * point[i].z - 4 * point[i].x - point[i].z * point[i].z) *
                        timeStep);
                point[i].z += static_cast<float>(
                        (-attractorParams[0] * point[i].z - 4 * point[i].x - 4 * point[i].y - point[i].x * point[i].x) *
                        timeStep);
            }
            break;
        }
        case 6: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>(
                        ((1 / attractorParams[1] - attractorParams[0]) * point[i].x + point[i].z +
                         point[i].x * point[i].y) * timeStep);
                point[i].y += static_cast<float>((-attractorParams[1] * point[i].y - point[i].x * point[i].x) *
                                                 timeStep);
                point[i].z += static_cast<float>((-point[i].x - attractorParams[2] * point[i].z) * timeStep);
            }
            break;
        }
        case 7: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>(
                        (-attractorParams[0] * point[i].x + point[i].y + 10.0f * point[i].y * point[i].z) *
                        timeStep);
                point[i].y += static_cast<float>((-point[i].x - 0.4 * point[i].y + 5.0f * point[i].x * point[i].z) *
                                                 timeStep);
                point[i].z += static_cast<float>((attractorParams[1] * point[i].z - 5.0f * point[i].x * point[i].y) *
                                                 timeStep);
            }
            break;
        }
        case 8: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>((point[i].y) * timeStep);
                point[i].y += static_cast<float>((-point[i].x + point[i].y * point[i].z) * timeStep);
                point[i].z += static_cast<float>((attractorParams[0] - point[i].y * point[i].y) * timeStep);
            }
            break;
        }
        case 9: {
            for (unsigned i = 0; i < numPoints; i++) {
                point[i].x += static_cast<float>((-attractorParams[0] * point[i].x + sin(point[i].y)) * timeStep);
                point[i].y += static_cast<float>((-attractorParams[0] * point[i].y + sin(point[i].z)) * timeStep);
                point[i].z += static_cast<float>((-attractorParams[0] * point[i].z + sin(point[i].x)) * timeStep);
            }
            break;
        }
    }

    // Move Left and Right
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        camPosition.x -= sin(camAngle[1] + PI / 2.0f) * 0.25f;
        camPosition.z -= cos(camAngle[1] + PI / 2.0f) * 0.25f;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        camPosition.x += sin(camAngle[1] + PI / 2.0f) * 0.25f;
        camPosition.z += cos(camAngle[1] + PI / 2.0f) * 0.25f;
    }

    // Move Forwards and Backwards
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        camPosition.z -= cos(camAngle[1]) * 0.25f;
        camPosition.x -= sin(camAngle[1]) * 0.25f;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        camPosition.z += cos(camAngle[1]) * 0.25f;
        camPosition.x += sin(camAngle[1]) * 0.25f;
    }

    // Move Up and Down
    if (Keyboard::isKeyPressed(Keyboard::LShift))
        camPosition.y += 0.1f;
    if (Keyboard::isKeyPressed(Keyboard::Space))
        camPosition.y -= 0.1f;

    /// Update Camera Angle

    // Look Left and Right
    if (Keyboard::isKeyPressed(Keyboard::Left))
        camAngle[1] -= 0.003f;
    if (Keyboard::isKeyPressed(Keyboard::Right))
        camAngle[1] += 0.003f;


    // Look Up and Down
    if (Keyboard::isKeyPressed(Keyboard::Up))
        camAngle[0] += 0.003f;
    if (Keyboard::isKeyPressed(Keyboard::Down))
        camAngle[0] -= 0.003f;

    /// Compute Rotation Matrixes

    rotMatrixX =
            {
                    {1, 0,                 0},
                    {0, cos(camAngle[0]),  sin(camAngle[0])},
                    {0, -sin(camAngle[0]), cos(camAngle[0])}
            };
    rotMatrixY =
            {
                    {cos(camAngle[1]), 0, -sin(camAngle[1])},
                    {0,                1, 0},
                    {sin(camAngle[1]), 0, cos(camAngle[1])}
            };
    rotMatrixZ =
            {
                    {cos(camAngle[2]),  sin(camAngle[2]), 0},
                    {-sin(camAngle[2]), cos(camAngle[2]), 0},
                    {0,                 0,                1}
            };


    // Change speed
    if (Keyboard::isKeyPressed(Keyboard::PageUp))
        speed += 0.025f;
    if (Keyboard::isKeyPressed(Keyboard::PageDown))
        speed -= 0.025f;
}

void DSAttractors::draw(RenderWindow &window) {
    // For every point
    for (unsigned g = 0; g < numPoints; g++) {
        /// Draw circle

        // Projection maths
        Vector3f d;
        d = point[g] - camPosition;
        d = rotMatrixX * (rotMatrixY * (rotMatrixZ * d));

        // Only if the point is infront of the camera
        if (d.z >= 0) {
            projectedPoint = {
                    displayPosition.z * d.x / d.z + displayPosition.x,
                    displayPosition.z * d.y / d.z + displayPosition.y
            };

            circle[g].setPosition(Vector2f(projectedPoint.x, projectedPoint.y));
            window.draw(circle[g]);
        }

        /// Draw trail

        /*
            The point of this algorithm is to use indexes in a clever manner in order to avoid shifting every
            previous position one across in "trail" every frame, which takes a lot of time. It flows like a
            "shifting" >for< loop.
        */

        trail[g][j[g]] = point[g];         // Add most recent position to trail at index j[g]
        j[g]++;                             // j[g] incremented every frame, shifting the beginning of the for loop.
        if (j[g] == trail[g].size() - 1) { // If j[g] gets to the final index, set it to 0
            j[g] = 0;
            trail[g][trail[g].size() - 1] = trail[g][trail[g].size() - 2]; // This has to be done.
        }

        int k = 0; // Index that goes from 0 to numPoints, used for colour

        // Starting from the index i right after j[g], then from 0 all the way to j[g].
        int i = j[g] + 1;
        while (i != j[g]) {

            // Project the front end of the trail
            Vector3f d1;
            d1 = trail[g][i] - camPosition;
            d1 = rotMatrixX * (rotMatrixY * (rotMatrixZ * d1));

            Vector2f proj1;
            proj1 = {displayPosition.z * d1.x / d1.z + displayPosition.x,
                     displayPosition.z * d1.y / d1.z + displayPosition.y};

            line[0].position = proj1;

            // Project the back end of the trail
            Vector3f d2;
            if (i == 0)
                d2 = trail[g][trail[g].size() - 2] - camPosition;
            else
                d2 = trail[g][i - 1] - camPosition;
            d2 = rotMatrixX * (rotMatrixY * (rotMatrixZ * d2));

            Vector2f proj2;
            proj2 = {displayPosition.z * d2.x / d2.z + displayPosition.x,
                     displayPosition.z * d2.y / d2.z + displayPosition.y};

            line[1].position = proj2;

            // Calculate trail colours
            Color fade;
            fade = Color(
                    clamp(colours[attractorIndex].r +
                          trailColoursParams[attractorIndex][0] * Magnitude(line[1].position - line[0].position)),
                    clamp(colours[attractorIndex].g +
                          trailColoursParams[attractorIndex][1] * Magnitude(line[1].position - line[0].position)),
                    clamp(colours[attractorIndex].b +
                          trailColoursParams[attractorIndex][2] * Magnitude(line[1].position - line[0].position)),
                    0 + static_cast<Uint8>((k * 255 / trail[g].size())));

            line[0].color = fade;
            line[1].color = fade;

            // Draw if both the front and end of the trail are in front of the camera
            if (d1.z >= 0 && d2.z >= 0)
                window.draw(line);

            // Increment counters
            i++;
            if (i == trail[g].size()) // Set i to 0 once it gets to the end of "trail"
                i = 0;

            k++;
        }
    }

    text.setString(attractorNames[attractorIndex]);
    text.setScale(0.1f, 0.1f);
    text.setPosition(Vector2f(-85, -45));
    window.draw(text);

    /// UNCOMMENT FOR ON-SCREEN COORDINATES
/*
    for (unsigned i = 0; i < numPoints; i++) {
        string coordinate_string = "(" + to_string(static_cast<int>(point[i].x)) + ", " +
                                   to_string(static_cast<int>(point[i].y)) + ", " +
                                   to_string(static_cast<int>(point[i].z)) + ")";
        text.setString(coordinate_string);
        text.setPosition(circle[i].getPosition() + Vector2f(1.0f, -5.0f));
        window.draw(text);
    }
*/
    window.display();
    window.clear(Color(0, 0, 0, 255));
}

void DSAttractors::run(RenderWindow &window) {
    window.setView(view);

    while (window.isOpen() && !endSubProgram) {
        this->input(window); // Get Input
        this->update();         // Update Graphics
        this->draw(window);  // Draw Graphics
    }

    window.setView(View(Vector2f(static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)),
                        Vector2f(static_cast<float>(screenWidth), static_cast<float>(screenHeight))));
}

DSAttractors::~DSAttractors() {}
