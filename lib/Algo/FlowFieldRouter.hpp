#pragma once

#include <vector>
#include <limits>
#include <queue>
#include <tuple>
#include <cstdint>
#include <algorithm>

class FlowFieldRouter {
private:
    int m_width;
    int m_height;
    
    // Flattened grid: m_grid[y * m_width + x]
    std::vector<uint8_t> m_grid; 
    std::vector<uint16_t> m_integrationField;
    std::vector<int> m_queueBuffer;

    const uint16_t UNREACHABLE = std::numeric_limits<uint16_t>::max();

    // Directions: N, S, E, W
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {-1, 1, 0, 0};

public:
    FlowFieldRouter(const std::vector<std::vector<int>>& grid, const int wallMask) 
        : m_width(grid[0].size()), m_height(grid.size()) {
        
        int size = width * height;
        m_grid.resize(size, 1); // Default to walls for safety
        m_integrationField.resize(size, UNREACHABLE);
        m_queueBuffer.reserve(size);

	// Map input grid to our grid
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                // 1D mapping: y * width + x
                // Store 0 for walkable, 1 for wall
                m_grid[y * m_width + x] = (inputGrid[y][x]&wallMask) ? 1 : 0;
            }
        }
    }

    // Call this ONCE per frame (or when target moves).
    // This generates the "scent" that all agents will follow.
    // maxRange: The maximum distance from the target to generate the field. -1 for infinite.
    void UpdateTarget(int targetX, int targetY, int maxRange = -1) {
        
        // If target is inside a wall, abort (or find nearest valid neighbor - simplified here to abort)
        int targetIdx = targetY * m_width + targetX;
        if (m_grid[targetIdx] == 1) return;

        // 1. Reset Integration Field
        // Using memset is faster than looping std::fill for POD types
        // 0xFFFF is -1 in 2's complement for short, acting as Max Value
        std::fill(m_integrationField.begin(), m_integrationField.end(), UNREACHABLE);

        // 2. BFS Initialization
        m_queueBuffer.clear();
        
        // Set target distance to 0
        m_integrationField[targetIdx] = 0;
        m_queueBuffer.push_back(targetIdx);

        // 3. High-Performance BFS
        size_t head = 0;
        while(head < m_queueBuffer.size()) {
            int currentIdx = m_queueBuffer[head++];
            
            int cx = currentIdx % m_width;
            int cy = currentIdx / m_width;
            uint16_t currentDist = m_integrationField[currentIdx];

            // Check 4 neighbors
            // We use direct array math where possible to avoid branching
            
            // Optimization: Unrolling the loop manually or keeping it tight.
            for (int i = 0; i < 4; ++i) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];

                int nIdx = ny * m_width + nx;

		// If walkable (0) and not visited (UNREACHABLE)
		if (m_grid[nIdx] == 0 && m_integrationField[nIdx] == UNREACHABLE) {

			// Check if we are exceeding the max range
			if (maxRange != -1 && (currentDist + 1) > maxRange) continue;

			m_integrationField[nIdx] = currentDist + 1;
			m_queueBuffer.push_back(nIdx);
		}
            }
        }
    }

    // Returns the {x, y} of the immediate next step.
    // If no path exists or already at target, returns {currentX, currentY}.
    std::pair<int, int> GetNextStep(int currentX, int currentY) const {
        int currentIdx = currentY * m_width + currentX;
        
        // If we are in a wall or unreachable area, don't move
        if (m_integrationField[currentIdx] == UNREACHABLE) 
            return {currentX, currentY};
            
        // If we are at the target (distance 0), stay there
        if (m_integrationField[currentIdx] == 0)
            return {currentX, currentY};

        uint16_t bestDist = m_integrationField[currentIdx];
        int bestX = currentX;
        int bestY = currentY;

        // pick the neighbor with the lowest distance value
        for (int i = 0; i < 4; ++i) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];

	    int nIdx = ny * m_width + nx;
	    uint16_t dist = m_integrationField[nIdx];

	    if (dist < bestDist) {
		    bestDist = dist;
		    bestX = nx;
		    bestY = ny;
	    }
        }

        return {bestX, bestY};
    }
};

