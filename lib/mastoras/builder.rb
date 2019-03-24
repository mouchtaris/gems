require_relative 'builders/vagrant'

module Mastoras
  class Builder
    class << self
      def inherited(sub)
        (@subordinates ||= []) << sub
      end

      def all
        @subordinates.to_enum.lazy
      end
    end
  end
end
