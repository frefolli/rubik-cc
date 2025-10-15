    switch (rotating.face_idx) {
      case 0: {
        if (rotating.direction) {
          faces[0].blocks = {faces[0].blocks[2], faces[0].blocks[3], faces[0].blocks[4], faces[0].blocks[5], faces[0].blocks[6], faces[0].blocks[7], faces[0].blocks[0], faces[0].blocks[1]};
        } else {          faces[0].blocks = {faces[0].blocks[6], faces[0].blocks[7], faces[0].blocks[0], faces[0].blocks[1], faces[0].blocks[2], faces[0].blocks[3], faces[0].blocks[4], faces[0].blocks[5]};
        }        faces[3].blocks[2] = faces[0].blocks[2];
        faces[3].blocks[1] = faces[0].blocks[3];
        faces[3].blocks[0] = faces[0].blocks[4];
        faces[4].blocks[2] = faces[0].blocks[1];
        faces[4].blocks[0] = faces[0].blocks[5];
        faces[4].blocks[1] = faces[0].center;
        faces[5].blocks[2] = faces[0].blocks[0];
        faces[5].blocks[0] = faces[0].blocks[6];
        faces[5].blocks[1] = faces[0].blocks[7];
        faces[6].blocks[2] = faces[0].blocks[4];
        faces[6].blocks[1] = faces[0].blocks[5];
        faces[6].blocks[0] = faces[0].blocks[6];
        faces[7].blocks[2] = faces[0].blocks[3];
        faces[7].blocks[0] = faces[0].blocks[7];
        faces[7].blocks[1] = faces[0].center;
        faces[8].blocks[0] = faces[0].blocks[0];
        faces[8].blocks[1] = faces[0].blocks[1];
        faces[8].blocks[2] = faces[0].blocks[2];
      }; break;
      case 1: {
        if (rotating.direction) {
          faces[1].blocks = {faces[1].blocks[2], faces[1].blocks[3], faces[1].blocks[4], faces[1].blocks[5], faces[1].blocks[6], faces[1].blocks[7], faces[1].blocks[0], faces[1].blocks[1]};
        } else {          faces[1].blocks = {faces[1].blocks[6], faces[1].blocks[7], faces[1].blocks[0], faces[1].blocks[1], faces[1].blocks[2], faces[1].blocks[3], faces[1].blocks[4], faces[1].blocks[5]};
        }        faces[3].blocks[3] = faces[1].blocks[2];
        faces[3].center = faces[1].blocks[3];
        faces[3].blocks[7] = faces[1].blocks[4];
        faces[4].blocks[3] = faces[1].blocks[1];
        faces[4].blocks[7] = faces[1].blocks[5];
        faces[4].center = faces[1].center;
        faces[5].blocks[3] = faces[1].blocks[0];
        faces[5].blocks[7] = faces[1].blocks[6];
        faces[5].center = faces[1].blocks[7];
        faces[6].blocks[3] = faces[1].blocks[4];
        faces[6].center = faces[1].blocks[5];
        faces[6].blocks[7] = faces[1].blocks[6];
        faces[7].blocks[3] = faces[1].blocks[3];
        faces[7].blocks[7] = faces[1].blocks[7];
        faces[7].center = faces[1].center;
        faces[8].blocks[7] = faces[1].blocks[0];
        faces[8].center = faces[1].blocks[1];
        faces[8].blocks[3] = faces[1].blocks[2];
      }; break;
      case 2: {
        if (rotating.direction) {
          faces[2].blocks = {faces[2].blocks[2], faces[2].blocks[3], faces[2].blocks[4], faces[2].blocks[5], faces[2].blocks[6], faces[2].blocks[7], faces[2].blocks[0], faces[2].blocks[1]};
        } else {          faces[2].blocks = {faces[2].blocks[6], faces[2].blocks[7], faces[2].blocks[0], faces[2].blocks[1], faces[2].blocks[2], faces[2].blocks[3], faces[2].blocks[4], faces[2].blocks[5]};
        }        faces[3].blocks[4] = faces[2].blocks[2];
        faces[3].blocks[5] = faces[2].blocks[3];
        faces[3].blocks[6] = faces[2].blocks[4];
        faces[4].blocks[4] = faces[2].blocks[1];
        faces[4].blocks[6] = faces[2].blocks[5];
        faces[4].blocks[5] = faces[2].center;
        faces[5].blocks[4] = faces[2].blocks[0];
        faces[5].blocks[6] = faces[2].blocks[6];
        faces[5].blocks[5] = faces[2].blocks[7];
        faces[6].blocks[4] = faces[2].blocks[4];
        faces[6].blocks[5] = faces[2].blocks[5];
        faces[6].blocks[6] = faces[2].blocks[6];
        faces[7].blocks[4] = faces[2].blocks[3];
        faces[7].blocks[6] = faces[2].blocks[7];
        faces[7].blocks[5] = faces[2].center;
        faces[8].blocks[6] = faces[2].blocks[0];
        faces[8].blocks[5] = faces[2].blocks[1];
        faces[8].blocks[4] = faces[2].blocks[2];
      }; break;
      case 3: {
        if (rotating.direction) {
          faces[3].blocks = {faces[3].blocks[2], faces[3].blocks[3], faces[3].blocks[4], faces[3].blocks[5], faces[3].blocks[6], faces[3].blocks[7], faces[3].blocks[0], faces[3].blocks[1]};
        } else {          faces[3].blocks = {faces[3].blocks[6], faces[3].blocks[7], faces[3].blocks[0], faces[3].blocks[1], faces[3].blocks[2], faces[3].blocks[3], faces[3].blocks[4], faces[3].blocks[5]};
        }        faces[0].blocks[2] = faces[3].blocks[2];
        faces[0].blocks[3] = faces[3].blocks[1];
        faces[0].blocks[4] = faces[3].blocks[0];
        faces[1].blocks[2] = faces[3].blocks[3];
        faces[1].blocks[3] = faces[3].center;
        faces[1].blocks[4] = faces[3].blocks[7];
        faces[2].blocks[2] = faces[3].blocks[4];
        faces[2].blocks[3] = faces[3].blocks[5];
        faces[2].blocks[4] = faces[3].blocks[6];
        faces[6].blocks[2] = faces[3].blocks[0];
        faces[6].blocks[4] = faces[3].blocks[6];
        faces[6].blocks[3] = faces[3].blocks[7];
        faces[7].blocks[2] = faces[3].blocks[1];
        faces[7].blocks[4] = faces[3].blocks[5];
        faces[7].blocks[3] = faces[3].center;
        faces[8].blocks[2] = faces[3].blocks[2];
        faces[8].blocks[3] = faces[3].blocks[3];
        faces[8].blocks[4] = faces[3].blocks[4];
      }; break;
      case 4: {
        if (rotating.direction) {
          faces[4].blocks = {faces[4].blocks[2], faces[4].blocks[3], faces[4].blocks[4], faces[4].blocks[5], faces[4].blocks[6], faces[4].blocks[7], faces[4].blocks[0], faces[4].blocks[1]};
        } else {          faces[4].blocks = {faces[4].blocks[6], faces[4].blocks[7], faces[4].blocks[0], faces[4].blocks[1], faces[4].blocks[2], faces[4].blocks[3], faces[4].blocks[4], faces[4].blocks[5]};
        }        faces[0].blocks[1] = faces[4].blocks[2];
        faces[0].blocks[5] = faces[4].blocks[0];
        faces[0].center = faces[4].blocks[1];
        faces[1].blocks[1] = faces[4].blocks[3];
        faces[1].blocks[5] = faces[4].blocks[7];
        faces[1].center = faces[4].center;
        faces[2].blocks[1] = faces[4].blocks[4];
        faces[2].blocks[5] = faces[4].blocks[6];
        faces[2].center = faces[4].blocks[5];
        faces[6].blocks[1] = faces[4].blocks[0];
        faces[6].blocks[5] = faces[4].blocks[6];
        faces[6].center = faces[4].blocks[7];
        faces[7].blocks[1] = faces[4].blocks[1];
        faces[7].blocks[5] = faces[4].blocks[5];
        faces[7].center = faces[4].center;
        faces[8].blocks[1] = faces[4].blocks[2];
        faces[8].center = faces[4].blocks[3];
        faces[8].blocks[5] = faces[4].blocks[4];
      }; break;
      case 5: {
        if (rotating.direction) {
          faces[5].blocks = {faces[5].blocks[2], faces[5].blocks[3], faces[5].blocks[4], faces[5].blocks[5], faces[5].blocks[6], faces[5].blocks[7], faces[5].blocks[0], faces[5].blocks[1]};
        } else {          faces[5].blocks = {faces[5].blocks[6], faces[5].blocks[7], faces[5].blocks[0], faces[5].blocks[1], faces[5].blocks[2], faces[5].blocks[3], faces[5].blocks[4], faces[5].blocks[5]};
        }        faces[0].blocks[0] = faces[5].blocks[2];
        faces[0].blocks[6] = faces[5].blocks[0];
        faces[0].blocks[7] = faces[5].blocks[1];
        faces[1].blocks[0] = faces[5].blocks[3];
        faces[1].blocks[6] = faces[5].blocks[7];
        faces[1].blocks[7] = faces[5].center;
        faces[2].blocks[0] = faces[5].blocks[4];
        faces[2].blocks[6] = faces[5].blocks[6];
        faces[2].blocks[7] = faces[5].blocks[5];
        faces[6].blocks[0] = faces[5].blocks[0];
        faces[6].blocks[6] = faces[5].blocks[6];
        faces[6].blocks[7] = faces[5].blocks[7];
        faces[7].blocks[0] = faces[5].blocks[1];
        faces[7].blocks[6] = faces[5].blocks[5];
        faces[7].blocks[7] = faces[5].center;
        faces[8].blocks[0] = faces[5].blocks[2];
        faces[8].blocks[7] = faces[5].blocks[3];
        faces[8].blocks[6] = faces[5].blocks[4];
      }; break;
      case 6: {
        if (rotating.direction) {
          faces[6].blocks = {faces[6].blocks[2], faces[6].blocks[3], faces[6].blocks[4], faces[6].blocks[5], faces[6].blocks[6], faces[6].blocks[7], faces[6].blocks[0], faces[6].blocks[1]};
        } else {          faces[6].blocks = {faces[6].blocks[6], faces[6].blocks[7], faces[6].blocks[0], faces[6].blocks[1], faces[6].blocks[2], faces[6].blocks[3], faces[6].blocks[4], faces[6].blocks[5]};
        }        faces[0].blocks[4] = faces[6].blocks[2];
        faces[0].blocks[5] = faces[6].blocks[1];
        faces[0].blocks[6] = faces[6].blocks[0];
        faces[1].blocks[4] = faces[6].blocks[3];
        faces[1].blocks[5] = faces[6].center;
        faces[1].blocks[6] = faces[6].blocks[7];
        faces[2].blocks[4] = faces[6].blocks[4];
        faces[2].blocks[5] = faces[6].blocks[5];
        faces[2].blocks[6] = faces[6].blocks[6];
        faces[3].blocks[0] = faces[6].blocks[2];
        faces[3].blocks[6] = faces[6].blocks[4];
        faces[3].blocks[7] = faces[6].blocks[3];
        faces[4].blocks[0] = faces[6].blocks[1];
        faces[4].blocks[6] = faces[6].blocks[5];
        faces[4].blocks[7] = faces[6].center;
        faces[5].blocks[0] = faces[6].blocks[0];
        faces[5].blocks[6] = faces[6].blocks[6];
        faces[5].blocks[7] = faces[6].blocks[7];
      }; break;
      case 7: {
        if (rotating.direction) {
          faces[7].blocks = {faces[7].blocks[2], faces[7].blocks[3], faces[7].blocks[4], faces[7].blocks[5], faces[7].blocks[6], faces[7].blocks[7], faces[7].blocks[0], faces[7].blocks[1]};
        } else {          faces[7].blocks = {faces[7].blocks[6], faces[7].blocks[7], faces[7].blocks[0], faces[7].blocks[1], faces[7].blocks[2], faces[7].blocks[3], faces[7].blocks[4], faces[7].blocks[5]};
        }        faces[0].blocks[3] = faces[7].blocks[2];
        faces[0].blocks[7] = faces[7].blocks[0];
        faces[0].center = faces[7].blocks[1];
        faces[1].blocks[3] = faces[7].blocks[3];
        faces[1].blocks[7] = faces[7].blocks[7];
        faces[1].center = faces[7].center;
        faces[2].blocks[3] = faces[7].blocks[4];
        faces[2].blocks[7] = faces[7].blocks[6];
        faces[2].center = faces[7].blocks[5];
        faces[3].blocks[1] = faces[7].blocks[2];
        faces[3].blocks[5] = faces[7].blocks[4];
        faces[3].center = faces[7].blocks[3];
        faces[4].blocks[1] = faces[7].blocks[1];
        faces[4].blocks[5] = faces[7].blocks[5];
        faces[4].center = faces[7].center;
        faces[5].blocks[1] = faces[7].blocks[0];
        faces[5].blocks[5] = faces[7].blocks[6];
        faces[5].center = faces[7].blocks[7];
      }; break;
      case 8: {
        if (rotating.direction) {
          faces[8].blocks = {faces[8].blocks[2], faces[8].blocks[3], faces[8].blocks[4], faces[8].blocks[5], faces[8].blocks[6], faces[8].blocks[7], faces[8].blocks[0], faces[8].blocks[1]};
        } else {          faces[8].blocks = {faces[8].blocks[6], faces[8].blocks[7], faces[8].blocks[0], faces[8].blocks[1], faces[8].blocks[2], faces[8].blocks[3], faces[8].blocks[4], faces[8].blocks[5]};
        }        faces[0].blocks[0] = faces[8].blocks[0];
        faces[0].blocks[1] = faces[8].blocks[1];
        faces[0].blocks[2] = faces[8].blocks[2];
        faces[1].blocks[0] = faces[8].blocks[7];
        faces[1].blocks[1] = faces[8].center;
        faces[1].blocks[2] = faces[8].blocks[3];
        faces[2].blocks[0] = faces[8].blocks[6];
        faces[2].blocks[1] = faces[8].blocks[5];
        faces[2].blocks[2] = faces[8].blocks[4];
        faces[3].blocks[2] = faces[8].blocks[2];
        faces[3].blocks[3] = faces[8].blocks[3];
        faces[3].blocks[4] = faces[8].blocks[4];
        faces[4].blocks[2] = faces[8].blocks[1];
        faces[4].blocks[3] = faces[8].center;
        faces[4].blocks[4] = faces[8].blocks[5];
        faces[5].blocks[2] = faces[8].blocks[0];
        faces[5].blocks[3] = faces[8].blocks[7];
        faces[5].blocks[4] = faces[8].blocks[6];
      }; break;
    }
