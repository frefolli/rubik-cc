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
  def __init__(self, blocks: list[int], center: int, axis: tuple[int, int, int]) -> None:
    self.blocks = blocks
    self.center = center
    self.axis = axis

  def check(self):
    assert len(self.blocks) == 8

  def print(self):
    print('Face::Load({' + ', '.join([str(_).rjust(2) for _ in self.blocks]) + '}, ' + str(self.center) + ', {.x = ' + str(self.axis[0]) + 'f, .y = ' + str(self.axis[1]) + 'f, .z = ' + str(self.axis[2]) + 'f}),')

  def rotate(self, anti: bool = False) -> Face:
    if anti:
      return Face(rotr2(self.blocks), self.center, self.axis)
    return Face(rotl2(self.blocks), self.center, self.axis)

faces = [
  Face([0, 1, 2, 5, 8, 7, 6, 3], 4, (0, 1, 0)),
  Face([9, 10, 11, 14, 17, 16, 15 ,12], 13, (0, 1, 0)),
  Face([18, 19, 20, 23, 26, 25, 24, 21], 22, (0, 1, 0)),

  Face([8, 5, 2, 11, 20, 23, 26, 17], 14, (0, 0, 1)),
  Face([7, 4, 1, 10, 19, 22, 25, 16], 13, (0, 0, 1)),
  Face([6, 3, 0, 9, 18, 21, 24, 15], 12, (0, 0, 1)),

  Face([24, 25, 26, 17, 8, 7, 6, 15], 16, (1, 0, 0)),
  Face([21, 22, 23, 14, 5, 4, 3, 12], 13, (1, 0, 0)),
  Face([18, 19, 20, 11, 2, 1, 0, 9], 10, (1, 0, 0)),
]

for face in faces:
  face.check()

slates = {}

for face_a in range(len(faces)):
  for face_b in range(len(faces)):
    if face_a != face_b:
      key = (face_a, face_b)
      if key not in slates:
        slates[key] = []
        for idx_a, el in enumerate(faces[face_a].blocks):
          if el in faces[face_b].blocks:
            idx_b = faces[face_b].blocks.index(el)
            slates[key].append((idx_a, idx_b))
        slates[key[::-1]] = [_[::-1] for _ in slates[key]]

indices = [0, 1, 2, 3, 4, 5, 6, 7]

print('\n\n/* FACES */\n\n')

for face in faces:
  face.print()

print('\n\n/* END OF ROTATION */\n\n')

print('    switch (rotating.face_idx) {')
for rotating_face in range(len(faces)):
  print('      case %s: {' % (rotating_face,))
  print('        if (rotating.direction) {')
  print('          faces[%s].blocks = {%s};' % (rotating_face, ', '.join(['faces[%s].blocks[%s]' % (rotating_face, idx) for idx in rotr2(indices)])))
  print('        } else {')
  print('          faces[%s].blocks = {%s};' % (rotating_face, ', '.join(['faces[%s].blocks[%s]' % (rotating_face, idx) for idx in rotl2(indices)])))
  print('        }')
  for affected_face in range(len(faces)):
    key = (rotating_face, affected_face)
    if key in slates:
      for (idx_rot, idx_aff) in slates[key]:
        print('        faces[%s].blocks[%s] = faces[%s].blocks[%s];' % (affected_face, idx_aff, rotating_face, idx_rot))
  print('      }; break;')
print('    }')
