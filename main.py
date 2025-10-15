from __future__ import annotations
"""
 6  7  8
 3  4  5
 0  1  2

15 16 17
12 13 14
 9 10 11

24 25 26
21 22 23
18 19 20
"""

def rotr2(arr):
  return arr[2:] + arr[:2]

def rotl2(arr):
  return arr[-2:] + arr[:-2]

class Face:
  def __init__(self, blocks: list[int], center: int, axis: list[float]) -> None:
    self.blocks = blocks
    self.center = center
    self.axis = [float(_) for _ in axis]

  def check(self):
    assert len(self.blocks) == 8

  def rotate(self, anti: bool = False) -> Face:
    if anti:
      return Face(rotr2(self.blocks), self.center, self.axis)
    return Face(rotl2(self.blocks), self.center, self.axis)

faces = [
  Face([ 0,  1,  2,  5,  8,  7,  6,  3],  4, [ 0,  1,  0]),
  Face([ 9, 10, 11, 14, 17, 16, 15 ,12], 13, [ 0,  1,  0]),
  Face([18, 19, 20, 23, 26, 25, 24, 21], 22, [ 0,  1,  0]),

  Face([ 8,  5,  2, 11, 20, 23, 26, 17], 14, [ 0,  0,  1]),
  Face([ 7,  4,  1, 10, 19, 22, 25, 16], 13, [ 0,  0,  1]),
  Face([ 6,  3,  0,  9, 18, 21, 24, 15], 12, [ 0,  0,  1]),

  Face([ 6,  7,  8, 17, 26, 25, 24, 15], 16, [ 1,  0,  0]),
  Face([ 3,  4,  5, 14, 23, 22, 21, 12], 13, [ 1,  0,  0]),
  Face([ 0,  1,  2, 11, 20, 19, 18,  9], 10, [ 1,  0,  0]),
]

for face in faces:
  face.check()

slates = {}

for face_a in range(len(faces)):
  for face_b in range(len(faces)):
    if face_a != face_b:
      key = (face_a, face_b)
      blocks_a = faces[face_a].blocks + [faces[face_a].center]
      blocks_b = faces[face_b].blocks + [faces[face_b].center]
      if key not in slates:
        slates[key] = []
        for idx_a, el in enumerate(blocks_a):
          if el in blocks_b:
            idx_b = blocks_b.index(el)
            slates[key].append((idx_a, idx_b))
        slates[key[::-1]] = [_[::-1] for _ in slates[key]]

indices = [0, 1, 2, 3, 4, 5, 6, 7]

with open("./src/faces.cc", 'w') as file:
  for face in faces:
    file.write('Face::Load({' + ', '.join([str(_).rjust(2) for _ in face.blocks]) + '}, ' + str(face.center) + ', {.x = ' + str(face.axis[0]) + 'f, .y = ' + str(face.axis[1]) + 'f, .z = ' + str(face.axis[2]) + 'f}),\n')

with open("./src/transition.cc", 'w') as file:
  file.write('    switch (rotating.face_idx) {\n')
  for rotating_face in range(len(faces)):
    file.write('      case %s: {\n' % (rotating_face,))
    file.write('        if (rotating.direction) {\n')
    file.write('          faces[%s].blocks = {%s};\n' % (rotating_face, ', '.join(['faces[%s].blocks[%s]' % (rotating_face, idx) for idx in rotr2(indices)])))
    file.write('        } else {')
    file.write('          faces[%s].blocks = {%s};\n' % (rotating_face, ', '.join(['faces[%s].blocks[%s]' % (rotating_face, idx) for idx in rotl2(indices)])))
    file.write('        }')
    for affected_face in range(len(faces)):
      key = (rotating_face, affected_face)
      if key in slates:
        for (idx_rot, idx_aff) in slates[key]:
          affected_str = 'faces[%s].blocks[%s]' % (affected_face, idx_aff)
          if idx_aff == 8:
            affected_str = 'faces[%s].center' % (affected_face,)
          rotating_str = 'faces[%s].blocks[%s]' % (rotating_face, idx_rot)
          if idx_rot == 8:
            rotating_str = 'faces[%s].center' % (rotating_face,)
          file.write('        %s = %s;\n' % (affected_str, rotating_str))
    file.write('      }; break;\n')
  file.write('    }\n')
