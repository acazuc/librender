#include "Draw.h"
#include <cmath>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

namespace librender
{

	void drawColorQuadBegin()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
	}

	void drawColorQuadEnd()
	{
		glEnd();
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

	void drawColorQuad(int x, int y, int width, int height, Color &topLeft, Color &topRight, Color &bottomRight, Color &bottomLeft)
	{
		drawColorQuadBegin();
		drawColorQuadPart(x, y, width, height, topLeft, topRight, bottomRight, bottomLeft);
		drawColorQuadEnd();
	}

	void drawColorQuad(int x, int y, int width, int height, Color &color)
	{
		drawColorQuad(x, y, width, height, color, color, color, color);
	}

	void drawColorQuadBorderBegin(float lineWidth)
	{
		glDisable(GL_LINE_SMOOTH);
		glBindTexture(GL_TEXTURE_2D, 0);
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
	}

	void drawColorQuadBorderEnd()
	{
		glEnd();
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

	void drawColorQuadBorder(int x, int y, int width, int height, Color &topLeftColor, Color &topRightColor, Color &bottomRightColor, Color &bottomLeftColor, float lineWidth)
	{
		drawColorQuadBorderBegin(lineWidth);
		drawColorQuadBorderPart(x, y, width, height, topLeftColor, topRightColor, bottomRightColor, bottomLeftColor);
		drawColorQuadBorderEnd();
	}

	void drawColorQuadBorder(int x, int y, int width, int height, Color &color, int lineWeight)
	{
		drawColorQuadBorder(x, y, width, height, color, color, color, color, lineWeight);
	}

	void drawQuadBegin(Texture *texture)
	{
		if (texture)
		{
			texture->bind();
		}
		glBegin(GL_QUADS);
	}

	void drawQuadEnd()
	{
		glEnd();
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

	void drawQuadPart(Texture *texture, int x, float y, int width, int height)
	{
		if (!texture)
			return;
		drawQuadPart(texture, x, y, width, height, 0, 0, texture->getWidth(), texture->getHeight());
	}

	void drawQuadPart(Texture *texture, int x, float y)
	{
		if (!texture)
			return;
		drawQuadPart(texture, x, y, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight());
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight, Color &color)
	{
		drawQuadBegin(texture);
		color.bind();
		drawQuadPart(texture, x, y, width, height, texXOrg, texYOrg, texCoWidth, texCoHeight);
		drawQuadEnd();
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight, float alpha)
	{
		drawQuadBegin(texture);
		glColor4f(1, 1, 1, alpha);
		drawQuadPart(texture, x, y, width, height, texXOrg, texYOrg, texCoWidth, texCoHeight);
		drawQuadEnd();
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, Color &color)
	{
		if (!texture)
			return;
		drawQuad(texture, x, y, width, height, 0, 0, texture->getWidth(), texture->getHeight(), color);
	}

	void drawQuad(Texture *texture, int x, int y, int width, int height, float alpha)
	{
		if (!texture)
			return;
		drawQuad(texture, x, y, width, height, 0, 0, texture->getWidth(), texture->getHeight(), alpha);
	}

	void drawQuad(Texture *texture, int x, int y, Color &color)
	{
		if (!texture)
			return;
		drawQuad(texture, x, y, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight(), color);
	}

	void drawQuad(Texture *texture, int x, int y, float alpha)
	{
		if (!texture)
			return;
		drawQuad(texture, x, y, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight(), alpha);
	}

	void drawCircleBegin(float lineWidth)
	{
		glLineWidth(lineWidth);
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_STRIP);
	}

	void drawCircleEnd()
	{
		glEnd();
		glDisable(GL_LINE_SMOOTH);
	}

	void drawCirclePart(int x, int y, int rayon, int nbSeg, float angle, float startAngle)
	{
		double step = angle / nbSeg;
		for (int i = 0; i < nbSeg + 1; ++i)
		{
			glVertex2d(rayon * cos(step * i + startAngle) + x + .5, rayon * sin(step * i + startAngle) + y + .5);
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

	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg, float lineWidth, float angle, float startAngle)
	{
		drawCircleBegin(lineWidth);
		color.bind();
		drawCirclePart(x, y, rayon, nbSeg, angle, startAngle);
		drawCircleEnd();
	}

	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg, float lineWidth)
	{
		drawCircle(x, y, rayon, color, nbSeg, lineWidth, 2 * (float)M_PI, 0);
	}

	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg)
	{
		drawCircle(x, y, rayon, color, nbSeg, 1, 2 * (float)M_PI, 0);
	}

	void drawCircle(int x, float y, int rayon, Color &color)
	{
		if (rayon < 30)
			drawCircle(x, y, rayon, color, M_PI * rayon, 1, 2 * (float)M_PI, 0);
		else
			drawCircle(x, y, rayon, color, rayon, 1, 2 * (float)M_PI, 0);
	}

	void drawLineBegin(float lineWidth)
	{
		glLineWidth(lineWidth);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_LINES);
	}

	void drawLineEnd()
	{
		glEnd();
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

	void drawLine(int x1, int y1, int x2, int y2, Color &color1, Color &color2, float lineWidth)
	{
		if (x1 != x2 && y1 != y2)
			glEnable(GL_LINE_SMOOTH);
		drawLineBegin(lineWidth);
		drawLinePart(x1, y1, x2, y2, color1, color2);
		drawLineEnd();
		if (x1 != x2 && y1 != y2)
			glDisable(GL_LINE_SMOOTH);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color1, Color &color2)
	{
		drawLine(x1, y1, x2, y2, color1, color2, 1);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color, float lineWidth)
	{
		drawLine(x1, y1, x2, y2, color, color, lineWidth);
	}

	void drawLine(int x1, int y1, int x2, int y2, Color &color)
	{
		drawLine(x1, y1, x2, y2, color, color, 1);
	}

	void drawPointBegin(float size)
	{
		glPointSize(size);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_POINTS);
	}

	void drawPointEnd()
	{
		glEnd();
	}

	void drawPointPart(int x, int y, Color &color)
	{
		color.bind();
		glVertex2f(x + .5f, y + .5f);
	}

	void drawPoint(int x, int y, Color &color, float size)
	{
		drawPointBegin(size);
		drawPointPart(x, y, color);
		drawPointEnd();
	}

	void drawPoint(float x, float y, Color &color)
	{
		drawPoint(x, y, color, 1);
	}

}
