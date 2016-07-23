class Ao
  def bye
    self.hello + " bye"
  end
  def self.init_scene(s0,s1,s2)
    Ao.setSpherePosition(
      s0[:x],s0[:y],s0[:z],
      s1[:x],s1[:y],s1[:z],
      s2[:x],s2[:y],s2[:z]
    )
  end
end
