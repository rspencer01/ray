#!/usr/bin/python

import random
import numpy as np
import os
random.seed(1)

COUNT = 40
M = 10
dt = 0.002
oversample = 10
DAMP = 5

def eg(r):
  r /= 0.04
  if r>3:
    return 0
  return 20*np.exp(-r**2*10) - 0.4 * np.exp(-(r-1)**2*4)
  r *= 4
  if r>0.718:
    r = 0.718
  return 1/(r+0.4) - np.exp(-(r-0.2)**2*8)

def fr(r):
  return (eg(r+0.00001)-eg(r)) / 0.00001

pos = np.array([
    [random.random()*2-1,
    random.random()*2-1,
    random.random()*2-1]
    for _ in xrange(COUNT)
    ])*0.2
vel = np.zeros((COUNT,3),dtype=float)

def write_out(index, glob=True):
  if not os.path.exists('output'):
    os.makedirs('output')
  s = \
  """w 100
h 100

m 0.1 0.2 0.1 0 0
s 0 -11 1 9.0

m 1 0.8 0.4 0.8 0
m 0.7 0.8 1.0 0.8 0.9
"""
  if glob:
    s+= "g {} 0.02 800\n".format(COUNT)

  for i in xrange(COUNT):
    if not glob:
      s+="s {} {} {} 0.02\n".format(*pos[i])
    else:
      s+="{} {} {}\n".format(*pos[i])
  open("output/water{}.scn".format(index),'w').write(s)

def energy():
  ke = 0
  pe = 0
  av = np.sum(vel,0)/COUNT
  for i in xrange(COUNT):
    ke += M * (vel[i]-av).dot(vel[i]-av) * 0.5
    for j in xrange(i):
      pe += eg((pos[i]-pos[j]).dot(pos[i]-pos[j])**0.5)
    if t>oversample*100:
      pe += 0.1*pos[i][1]*M
  return pe , ke

pos[:,2] = vel[:,2] = 0
pos -= np.sum(pos,0)/COUNT
stats = open('stats','w')

def calculate_forces(pos, t):
  forces =  np.zeros((COUNT,3),dtype=np.float)
  av = np.sum(vel,0)/COUNT
  for p1 in xrange(COUNT):
    for p2 in xrange(p1):
      r = sum([(pos[p1][k]-pos[p2][k])**2 for k in xrange(3)])**0.5
      forces[p1] += fr(r)*(pos[p2]-pos[p1])/r
      forces[p2] += fr(r)*(pos[p1]-pos[p2])/r
    forces[p1] += -DAMP * (vel[p1]-av)
    if (t > oversample*100):
      forces[p1] += np.array([0,-.1,0])*M
  return forces



for t in xrange(oversample*800):
  pe,ke = energy()
  ene = (pe+ke)/COUNT
  print t, ene, ke/COUNT, pe/COUNT
  if t%oversample == 0:
    write_out(t/oversample)
    stats.write("{} {} {} {} {} {}\n".format(
      t/oversample,
      ene,
      ke/COUNT,
      pe/COUNT,
      np.sum(vel,0)[1]/COUNT,
      np.sum(pos,0)[1]/COUNT))
    stats.flush()

  DAMP = 0
  if t < oversample*100:
    DAMP = 60
  elif t > oversample*400:
    DAMP = 5
  else:
    if ene > -1.32:
      DAMP = 15
    if DAMP > 0 and ene < -1.35:
      DAMP = 0
  forces = calculate_forces(pos, t)

  vel2 = vel + dt * forces / (2 * M)
  pos2 = pos + dt * vel / 2

  forces = calculate_forces(pos2, t)

  for i in xrange(COUNT):
    pos[i]+= dt * vel[i]

    vel[i] += dt * forces[i]/M

    if pos[i][1] < -.4:
      pos[i][1] = -.4
      vel[i][1] = 0
    if pos[i][0] < -.2:
      pos[i][0] = -.2
      vel[i][0] = 0
    if pos[i][0] > .2:
      pos[i][0] = .2
      vel[i][0] = 0

