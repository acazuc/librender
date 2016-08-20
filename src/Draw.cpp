#include "Draw.h"
#include <cmath>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

namespace librender
{

	void drawColorQuad(int x, int y, int width, int height, Color &topLeft, Color &topRight, Color &bottomRight, Color &bottomLeft)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
		drawColorQuadPart(x, y, width, height, topLeft, topRight, bottomRight, bottomLeft);
		glEnd();
	}

	void drawColorQuad(int x, int y, int width, int height, Color &color)
	{
		drawColorQuad(x, y, width, height, color, color, color, color);
	}

	void drawColorQuadPart(int x, int y, int width, int height, Color &topLeft, Color &topRight, Color &bottomRight, Color &bottomLeft)
	{
		topLeft.bind();
		glVertex2f(x, y);
		topRight.bind();
		glVertex2f(x + width, y);
		bottomRight.bind();
		glVertex2f(x + width, y + height);
		bottomLeft.bind();
		glVertex2f(x, y + height);
	}

	void drawColorQuadPart(int x, int y, int width, int height, Color &color)
	{
		drawColorQuadPart(x, y, width, height, color, color, color, color);
	}

	void drawColorQuadBorder(int x, int y, int width, int height, Color &topLeftColor, Color &topRightColor, Color &bottomRightColor, Color &bottomLeftColor, int lineWeight)
	{
		glDisable(GL_LINE_SMOOTH);
		glBindTexture(GL_TEXTURE_2D, 0);
		glLineWidth(lineWeight);
		glBegin(GL_LINE_LOOP);
		drawColorQuadBorderPart(x, y, width, height, topLeftColor, topRightColor, bottomRightColor, bottomLeftColor);
		glEnd();
	}

	void drawColorQuadBorder(int x, int y, int width, int height, Color &color, int lineWeight)
	{
		drawColorQuadBorder(x, y, width, height, color, color, color, color, lineWeight);
	}

	void drawColorQuadBorderPart(int x, int y, int width, int height, Color &topLeftColor, Color &topRightColor, Color &bottomRightColor, Color &bottomLeftColor)
	{
		topLeftColor.bind();
		glVertex2f(x + .5f, y + .5f);
		topRightColor.bind();
		glVertex2f(x + width + .5f, y + .5f);
		bottomRightColor.bind();
		glVertex2f(x + width + .5f, y + height + .5f);
		bottomLeftColor.bind();
		glVertex2f(x + .5f, y + height + .5f);
	}

	void drawColorQuadBorderPart(int x, int y, int width, int height, Color &color)
	{
		drawColorQuadBorderPart(x, y, width, height, color, color, color, color);
	}

	void drawQuadPart(Texture *texture, int x, float y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight)
	{
		if (texture)
		{
			float xFrom = texXOrg / static_cast<float>(texture->getWidth());
			float xTo = (texXOrg + texCoWidth) / static_cast<float>(texture->getWidth());
			float yFrom = texYOrg / static_cast<float>(texture->getHeight());
			float yTo = (texYOrg+texCoHeight) / static_cast<float>(texture->getHeight());
			glTexCoord2f(xFrom, yFrom);
			glVertex2f(x, y);
			glTexCoord2f(xFrom, yTo);
			glVertex2f(x, y + height);
			glTexCoord2f(xTo, yTo);
			glVertex2f(x + width, y + height);
			glTexCoord2f(xTo, yFrom);
			glVertex2f(x + width, y);
		}
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight, Color &color)
	{
		if (texture)
		{
			texture->bind();
			glBegin(GL_QUADS);
			color.bind();
			drawQuadPart(texture, x, y, width, height, texXOrg, texYOrg, texCoWidth, texCoHeight);
			glEnd();
		}
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight, float alpha)
	{
		if (texture)
		{
			texture->bind();
			glBegin(GL_QUADS);
			glColor4f(1, 1, 1, alpha);
			drawQuadPart(texture, x, y, width, height, texXOrg, texYOrg, texCoWidth, texCoHeight);
			glEnd();
		}
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, Color &color)
	{
		if (texture)
		{
			drawQuad(texture, x, y, width, height, 0, 0, texture->getWidth(), texture->getHeight(), color);
		}
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, float alpha)
	{
		if (texture)
		{
			drawQuad(texture, x, y, width, height, 0, 0, texture->getWidth(), texture->getHeight(), alpha);
		}
	}

	void drawQuad(Texture *texture, int x, int y, Color &color)
	{
		if (texture)
		{
			drawQuad(texture, x, y, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight(), color);
		}
	}

	void drawQuad(Texture *texture, int x, int y, float alpha)
	{
		if (texture)
		{
			drawQuad(texture, x, y, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight(), alpha);
		}
	}

	void drawCirclePart(int x, int y, int rayon, int nbSeg, float angle, float startAngle)
	{
		for (int i = 0; i < nbSeg + 1; ++i)
		{
			glVertex2d(rayon * cos(angle * i / nbSeg + startAngle) + x, rayon * sin(angle * i / nbSeg + startAngle) + y);
		}
	}

	void drawCirclePart(int x, int y, int rayon, int nbSeg)
	{
		drawCirclePart(x, y, rayon, nbSeg, 2 * (float)M_PI, 0);
	}

	void drawCirclePart(int x, int y, int rayon)
	{
		drawCirclePart(x, y, rayon, (int)(M_PI * rayon), 2 * (float)M_PI, 0);
	}

	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg, float lineWeight, float angle, float startAngle)
	{
		glLineWidth(lineWeight);
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_LINE_SMOOTH);
		color.bind();
		glBegin(GL_LINE_STRIP);
		drawCirclePart(x + .5f, y + .5f, rayon, nbSeg, angle, startAngle);
		glEnd();
		glDisable(GL_LINE_SMOOTH);
	}

	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg, float lineWeight)
	{
		drawCircle(x, y, rayon, color, nbSeg, lineWeight, 2 * (float)M_PI, 0);
	}

	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg)
	{
		drawCircle(x, y, rayon, color, nbSeg, 1, 2 * (float)M_PI, 0);
	}

	void drawCircle(int x, float y, int rayon, Color &color)
	{
		drawCircle(x, y, rayon, color, (int)(M_PI * rayon), 1, 2 * (float)M_PI, 0);
	}

	void drawLinePart(int x1, int y1, int x2, int y2, Color &color1, Color &color2)
	{
		color1.bind();
		glVertex2f(x1 + .5f, y1 + .5f);
		color2.bind();
		glVertex2f(x2 + .5f, y2 + .5f);
	}

	void drawLinePart(int x1, int y1, int x2, int y2, Color &color1)
	{
		drawLinePart(x1, y1, x2, y2, color1, color1);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color1, Color &color2, float lineWeight)
	{
		glLineWidth(lineWeight);
		glBindTexture(GL_TEXTURE_2D, 0);
		if(x1 != x2 && y1 != y2) {
			glEnable(GL_LINE_SMOOTH);
		}
		glBegin(GL_LINES);
		drawLinePart(x1, y1, x2, y2, color1, color2);
		glEnd();
		glDisable(GL_LINE_SMOOTH);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color1, Color &color2)
	{
		drawLine(x1, y1, x2, y2, color1, color2, 1);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color, float lineWeight)
	{
		drawLine(x1, y1, x2, y2, color, color, lineWeight);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color)
	{
		drawLine(x1, y1, x2, y2, color, color, 1);
	}

	void drawPoint(int x, int y, Color &color, float size)
	{
		glPointSize(size);
		glBindTexture(GL_TEXTURE_2D, 0);
		color.bind();
		glBegin(GL_POINTS);
		glVertex2f(x + .5f, y + .5f);
		glEnd();
	}

	void drawPoint(float x, float y, Color &color)
	{
		drawPoint(x, y, color, 1);
	}

}
