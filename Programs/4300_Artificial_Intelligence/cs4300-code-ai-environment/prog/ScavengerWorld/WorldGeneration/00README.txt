To generate a new set of objects and a world to use them, run the
NewWorld.bash script.  It generates 4 files:

- full_object_file="${prefix}_objects_full.txt"
  This file contains all of the possible objects for this world.
  Your agent should never look a this file.
  
- pickup_file="${prefix}_objects_pickup.csv"
  This file contains example classifications of objects for
  whether they should be picked up or not.  Your agent should
  use the contents of this file to learn a decision tree for
  deciding whether an object should be picked up or not.

- value_file="${prefix}_objects_value.csv"
  This file contains example classifications of objects for
  their approximate value.  Your agent should use the contents
  of this file to learn a decision tree for deciding the relative
  value of an object.

  The classification values are of the form: N_1_4 or P_1_4, where
  an 'N' prefix means a negative value, and a 'P' prefix means a
  positive value.  The '1_4' means the value is from 1 to 4.

- world_file="${prefix}_world.txt"
  This is the world file to give to the environment process.  Your
  agent should never look at this file.



