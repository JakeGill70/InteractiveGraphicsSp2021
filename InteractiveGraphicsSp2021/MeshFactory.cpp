#include "MeshFactory.hpp"
#include "OGLVertexMesh.hpp"

template <>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::CircularMeshXY(float radius, RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   float x, y, radians;
   for (float theta = 0; theta <= 360; theta += steps) {
      radians = glm::radians(theta);
      x = radius * cosf(radians);
      y = radius * sinf(radians);
      mesh->AddVertexData({ x, y, 0, color });
      radians = glm::radians(theta + steps);
      x = radius * cosf(radians);
      y = radius * sinf(radians);
      mesh->AddVertexData({ x, y, 0, color });
   }
   return mesh;
}

template <>
AbstractVertexMesh<VertexPCNT>* MeshFactory<VertexPCNT, RGBA>::DiskMeshXY(float radius, RGBA color, int steps)
{
   OGLVertexMesh<VertexPCNT>* mesh = new OGLVertexMesh<VertexPCNT>();
   TexCoord tex = { 0, 0 };
   float x, y, radians;
   for (float theta = 0; theta <= 360; theta += steps) {
      radians = glm::radians(theta);
      x = radius * cosf(radians);
      y = radius * sinf(radians);
      tex.S = (cosf(radians) + 1) / 2.0f;
      tex.T = (sinf(radians) + 1) / 2.0f;
      mesh->AddVertexData({ x, y, 0, color, {0, 0, 1}, tex });

      radians = glm::radians(theta + steps);
      x = radius * cosf(radians);
      y = radius * sinf(radians);
      tex.S = (cosf(radians) + 1) / 2.0f;
      tex.T = (sinf(radians) + 1) / 2.0f;
      mesh->AddVertexData({ x, y, 0, color, {0, 0, 1}, tex });

      tex.S = 0.5f;
      tex.T = 0.5f;
      mesh->AddVertexData({ 0, 0, 0, color, {0, 0, 1}, tex });
   }
   return mesh;
}

template <>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::SpirographMeshXY(
   float R, float l, float k, float revolutions, RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   VertexPC V;
   float x, y, radians, q = (1 - k) / k;
   float degrees = 360.0f * revolutions;
   for (float theta = 0; theta <= degrees; theta += steps) {
      radians = glm::radians(theta);
      x = R * (((1 - k) * cosf(radians)) + (l * k * cosf(q * radians)));
      y = R * (((1 - k) * sinf(radians)) - (l * k * sinf(q * radians)));
      V = { x, y, 0, color.red, color.green, color.blue };
      mesh->AddVertexData(V);
      radians = glm::radians(theta + steps);
      x = R * (((1 - k) * cosf(radians)) + (l * k * cosf(q * radians)));
      y = R * (((1 - k) * sinf(radians)) - (l * k * sinf(q * radians)));
      V = { x, y, 0, color.red, color.green, color.blue };
      mesh->AddVertexData(V);
   }
   return mesh;
}

template <>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::QuadraticBezierXY(
   glm::vec3 points[], RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   glm::vec3 Q0;
   VertexPC V;
   float tick = 1.0f / steps;
   for (float t = 0; t <= 1; t += tick) {
      float coef = 1 - t;
      float coef2 = coef * coef;
      Q0 = (coef2 * points[0])
         + (2 * coef * t * points[1])
         + (t * t * points[2]);
      V = { Q0.x, Q0.y, Q0.z, color};
      mesh->AddVertexData(V);
      float t2 = t + tick;
      coef = 1 - t2;
      coef2 = coef * coef;
      Q0 = (coef2 * points[0])
         + (2 * coef * t2 * points[1])
         + (t2 * t2 * points[2]);
      V = { Q0.x, Q0.y, Q0.z, color };
      mesh->AddVertexData(V);
   }
   return mesh;
}

template<>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::QuadraticBezierMatrixXY(glm::vec3 points[], RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   glm::mat3 CM{};
   CM[0] = glm::vec3(1, -2, 1);
   CM[1] = glm::vec3(-2, 2, 0);
   CM[2] = glm::vec3(1, 0, 0);
   glm::mat3 PM{};
   PM[0] = points[0];
   PM[1] = points[1];
   PM[2] = points[2];
   glm::vec3 tv = { 0, 0, 1 };
   glm::vec3 Q0;
   VertexPC V;
   float tick = 1.0f / steps;
   for (float t = 0; t <= 1; t += tick) {
      tv[0] = t * t;
      tv[1] = t;
      Q0 = PM * CM * tv;
      V = { Q0.x, Q0.y, Q0.z, color };
      mesh->AddVertexData(V);
      float t2 = t + tick;
      tv[0] = t2 * t2;
      tv[1] = t2;
      Q0 = PM * CM * tv;
      V = { Q0.x, Q0.y, Q0.z, color };
      mesh->AddVertexData(V);
   }
   return mesh;
}

template<>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::CubicBezierXY(
   glm::vec3 points[], RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   glm::vec3 C0;
   VertexPC V;
   float tick = 1.0f / steps;
   for (float t = 0; t <= 1; t += tick) {
      float coef = 1 - t;
      float coef2 = coef * coef;
      float coef3 = coef * coef * coef;
      C0 = (coef3 * points[0])
         + (3 * coef2 * t * points[1])
         + (3 * coef * t * t * points[2])
         + (t * t * t * points[3]);
      V = { C0.x, C0.y, C0.z, color };
      mesh->AddVertexData(V);
      float t2 = t + tick;
      coef = 1 - t2;
      coef2 = coef * coef;
      coef3 = coef * coef * coef;
      C0 = (coef3 * points[0])
         + (3 * coef2 * t2 * points[1])
         + (3 * coef * t2 * t2 * points[2])
         + (t2 * t2 * t2 * points[3]);
      V = { C0.x, C0.y, C0.z, color };
      mesh->AddVertexData(V);
   }
   return mesh;
}

template<>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::CubicBezierMatrixXY(
   glm::vec3 points[], RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   glm::mat4 CM{};
   CM[0] = glm::vec4(-1, 3, -3, 1);
   CM[1] = glm::vec4(3, -6, 3, 0);
   CM[2] = glm::vec4(-3, 3, 0, 0);
   CM[3] = glm::vec4(1, 0, 0, 0);
   glm::mat4 PM{};
   PM[0] = glm::vec4(points[0], 1);
   PM[1] = glm::vec4(points[1], 1);
   PM[2] = glm::vec4(points[2], 1);
   PM[3] = glm::vec4(points[3], 1);
   glm::vec4 tv = { 0, 0, 0, 1 };

   glm::vec3 C0;
   VertexPC V;
   float tick = 1.0f / steps;
   for (float t = 0; t <= 1; t += tick) {
      tv[0] = t * t * t;
      tv[1] = t * t;
      tv[2] = t;
      C0 = PM * CM * tv;
      V = { C0.x, C0.y, C0.z, color };
      mesh->AddVertexData(V);
      float t2 = t + tick;
      tv[0] = t2 * t2 * t2;
      tv[1] = t2 * t2;
      tv[2] = t2;
      C0 = PM * CM * tv;
      V = { C0.x, C0.y, C0.z, color };
      mesh->AddVertexData(V);
   }
   return mesh;
}

template<>
AbstractVertexMesh<VertexPC>* MeshFactory<VertexPC, RGB>::CubicBezierPatch(
   glm::vec3 points[][4], RGB color, int steps)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   mesh->SetPrimitive(GL_LINES);
   glm::mat4 CM{};
   CM[0] = glm::vec4(-1, 3, -3, 1);
   CM[1] = glm::vec4(3, -6, 3, 0);
   CM[2] = glm::vec4(-3, 3, 0, 0);
   CM[3] = glm::vec4(1, 0, 0, 0);
   glm::mat4 Px{}, Py{}, Pz{};
   for (auto row = 0; row < 4; row++) {
      for (auto col = 0; col < 4; col++) {
         Px[row][col] = points[row][col].x;
         Py[row][col] = points[row][col].y;
         Pz[row][col] = points[row][col].z;
      }
   }
   glm::vec4 sv = { 0, 0, 0, 1 };
   glm::vec4 tv = { 0, 0, 0, 1 };
   float x, y, z;
   float tick = 1.0f / steps;
   // endTick accounts for a rounding error when checking for
   // 1 inclusive (s <= 1 in the loop below)
   float endTick = 1.0f + (tick / 2.0f);
   vector<glm::vec3> vertices;
   
   for (float s = 0; s <= endTick; s += tick) { // The columns
      sv[0] = s * s * s;
      sv[1] = s * s;
      sv[2] = s;
      for (float t = 0; t <= endTick; t += tick) { // The rows
         tv[0] = t * t * t;
         tv[1] = t * t;
         tv[2] = t;
         x = glm::dot(sv, CM * Px * CM * tv);
         y = glm::dot(sv, CM * Py * CM * tv);
         z = glm::dot(sv, CM * Pz * CM * tv);
         vertices.push_back({ x, y, z });
      }
   }
   // Since the range is from 0 to 1 inclusive we'll have one extra row
   // and column. We have to add 1 to step.
   int index;
   VertexPC V1, V2, V3, V4;
   // V1 +--+ V4
   //    |\ |
   //    | \|
   // V2 +--+ V3
   int row = 0, col = 0;
   for (col = 0; col < steps; col++) {
      for (row = 0; row < steps; row++) {
         // Use column-major calculations
         index = col * (steps + 1) + row;
         x = vertices[index].x;
         y = vertices[index].y;
         z = vertices[index].z;
         V1 = { x, y, z, color };
         index = col * (steps + 1) + (row + 1);
         x = vertices[index].x;
         y = vertices[index].y;
         z = vertices[index].z;
         V2 = { x, y, z, color };
         index = (col + 1) * (steps + 1) + (row + 1);
         x = vertices[index].x;
         y = vertices[index].y;
         z = vertices[index].z;
         V3 = { x, y, z, color };
         index = (col + 1) * (steps + 1) + row;
         x = vertices[index].x;
         y = vertices[index].y;
         z = vertices[index].z;
         V4 = { x, y, z, color };
         mesh->AddVertexData(V1);
         mesh->AddVertexData(V2);
         mesh->AddVertexData(V1);
         mesh->AddVertexData(V3);
         mesh->AddVertexData(V1);
         mesh->AddVertexData(V4);
         mesh->AddVertexData(V3);
         mesh->AddVertexData(V4);
      }
      // Draw a line segment on the last row
      mesh->AddVertexData(V2);
      mesh->AddVertexData(V3);
   }
   mesh->SetUpAttributes("PC");
   return mesh;
}
