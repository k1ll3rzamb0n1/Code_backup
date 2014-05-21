#System Components
k1 = 1
k2 = 1
m1 = 1
m2 = 1
gravity = EffortSource(-9.8)
spring1 = CComponent(k1)
spring2 = CComponent(k2)
mass1 = IComponent(m1)
mass2 = IComponent(m2)

#Setup simulation time
dt = 0.1
end_time = 50.0
time = 0.0

#simulation loop
while( time < end_time ):
	#Gather Velocities from masses
	velocity1 = mass1.getFlow()
	velocity2 = mass2.getFlow()
	
	#Apply velocities to springs
	spring1.applyFlow(mass1.state / mass1.i, dt)
	spring2.applyFlow( (mass2.state / mass2.i) - (mass1.state / mass1.i), dt )
	
	#Gather mass Efforts
	mass1pe = gravity.getEffort() + spring2.getEffort() - spring1.getEffort()
	mass2pe = gravity.getEffort() - spring2.getEffort()
	
	#Apply Mass Efforts
	mass1.applyEffort( mass1pe, dt )
	mass2.applyEffort( mass2pe, dt )
	
	#Advance Time Steps
	time = time + dt