require_relative 'util/lazy_block'

module Variables
  class << self
    def injection(scroll, variables_def = nil)
      return Util::LazyBlock.new(method(:injection)) unless variables_def
      variables_def.merge(
        'mastoras::artifact_name' => scroll.name
      )
    end
  end
end
