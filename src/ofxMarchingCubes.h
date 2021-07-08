/* 
 * Copyright (c) 2009, Rui Madeira
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * http://creativecommons.org/licenses/LGPL/2.1/
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include "ofMain.h"
#include "Tables.h"
#include "ofxMCTypes.h"
#include "ofxSTL.h"

//marching cubes algorithm implementation based on the explanations and source in this page: http://local.wasp.uwa.edu.au/~pbourke/geometry/polygonise/

class ofxMarchingCubes{
public:
	ofxMarchingCubes();
	virtual ~ofxMarchingCubes();
	void init(const glm::vec3& _iniGridPos, const glm::vec3& gridSize, unsigned int _gridResX,unsigned int _gridResY,unsigned int _gridResZ);
	void clear();
	void update(float _threshold, bool bCalcNormals = false);
	virtual void draw(){debugDraw();}
	void debugDraw();
	void drawWireFrame();
	void drawFilled();
	void drawCube();
	void drawGrid();
	void addMetaBall(const glm::vec3& pos, float force);
	void setIsoValue(unsigned int gridX, unsigned int gridY, unsigned int gridZ, float value);
	float getIsoValue(unsigned int gridX, unsigned int gridY, unsigned int gridZ);
	void resetIsoValues(); //set all values to 0
	float getMaxIsoValue();
	float getMinIsoValue();
	float getAverageIsoValue();
	void scaleIsoValues(float amount); //multiplies
	void shiftIsoValues(float amount); //adds
	void normalizeIsoValues();
	void rescaleIsoValues(float min, float max);
	void absoluteValues();
	int getNumTriangles();
	float getThreshold();
	vector<glm::vec3>& getVertices();
	vector<glm::vec3>& getNormals();
	ofxMCGridValues& getIsoValues();
	ofxMCGridPoints& getGrid();
	void setGridPos(const glm::vec3& _gridPos);
	void setGridSize(const glm::vec3& _gridSize);
	void setGridRes(unsigned int gridResX, unsigned int gridResY, unsigned int gridResZ);
	glm::vec3 getGridPos();
	glm::vec3 getGridSize();
	glm::vec3 getGridRes();

	void saveModel(string fileName, bool bUseASCII_mode = false);
	ofxSTLExporter& getSTLExporter();
	
protected:
	ofxSTLExporter stlExporter;
	void setupGrid();
	int gridResX, gridResY, gridResZ;
	glm::vec3 iniGridPos;
	glm::vec3 gridSize;
	int numTriangles; 
	float threshold; 
	vector<glm::vec3>vertices;
	vector<glm::vec3>normals;
	glm::vec3 vertList[12];
	
	ofxMCGridValues isoValues;
	ofxMCGridPoints gridPoints;
	
	void vertexInterp(float isoLevel,const glm::vec3& p1, const glm::vec3& p2, float valp1, float valp2, glm::vec3& theVertice);
	void polygonise(uint i, uint j, uint k, bool bCalcNormals);
};















