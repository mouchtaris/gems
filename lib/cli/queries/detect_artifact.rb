module Cli
  module Queries
    class DetectArtifact < Query
      def perform(_)
        require 'pathname'
        Pathname.new(Dir.pwd).basename.to_s
      end
    end
  end
end
