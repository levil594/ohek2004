void RenderRectangle(float x, float y, float width, float height)
{
    // Draw filled rectangle (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw border (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void RenderGround(float yPosition, float height)
{
    // Draw ground (R:255, G:200, B:15)
    glColor3f(1.0f, 0.7843f, 0.0588f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, yPosition);
    glVertex2f(1.0f, yPosition);
    glVertex2f(1.0f, yPosition + height);
    glVertex2f(-1.0f, yPosition + height);
    glEnd();
}

void RenderObstacle(float x, float y, float width, float height)
{
    // Draw obstacle (R:0, G:255, B:0)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}